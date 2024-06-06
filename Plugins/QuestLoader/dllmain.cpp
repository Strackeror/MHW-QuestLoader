// dllmain.cpp : Defines the entry point for the DLL application.

#include "loader.h"
#include "scanmem.h"
#include "signatures.h"
#include "util.h"
#include <filesystem>
#include <unordered_map>

using namespace loader;
using namespace plugin;

std::string_view plugin::module_name = "QuestLoader";

const size_t CHECK_COMPLETE_OFFSET = 0x4e1;
const size_t CHECK_PROGRESS_OFFSET = 0x6d2;
const size_t OPTIONAL_COUNT_OFFSETT = 0x5f;
const size_t OPTIONAL_AT_OFFSET = 0x81;

static void (*increase_capacity)(void *, uint32_t) = nullptr;

class Quest {
public:
  int file_id;

  struct {
    void *vtable = nullptr;
    long long questId;

    char stuff[0x50];
  } questNoListObj;

  int starcount = 10;
  std::string questPath;

  Quest(int id) : file_id(id) {
    char buf[250];
    sprintf_s(buf, "quest\\questData_%05d", id);
    questPath = buf;

    questNoListObj.questId = id;
  }
};

static const int QuestMinId = 90000;
size_t AddedQuestCount;
std::vector<Quest> AddedQuests;
std::unordered_map<int, Quest *> QuestIds;

static void PopulateQuests() {
  if (!std::filesystem::exists("nativePC\\quest"))
    return;
  for (auto &entry : std::filesystem::directory_iterator("nativePC\\quest")) {
    std::string name = entry.path().filename().string();
    if (entry.path().filename().extension().string() != ".mib")
      continue;

    int id;
    if (sscanf_s(name.c_str(), "questData_%d.mib", &id) != 1)
      continue;
    if (id < 90000)
      continue;

    log(INFO, "Registered quest at {}", entry.path().string());
    AddedQuests.push_back(Quest(id));
  }

  for (auto &quest : AddedQuests) {
    QuestIds.insert({quest.file_id, &quest});
  }
  AddedQuestCount = AddedQuests.size();
}

bool QuestExists(int id) { return QuestIds.count(id); }

Quest *GetQuest(int id) { return QuestIds.find(id)->second; }

void ModifyQuestData(void *obj) {
  auto file = (char *)obj + 0xc;
  for (auto &quest : AddedQuests) {
    if (quest.questPath == std::string(file)) {
      *(int *)((char *)obj + 0xb0 + 0x30) = (int)quest.file_id;
      quest.starcount = *offsetPtr<unsigned char>(obj, 0xb0 + 0x34);
      log(INFO, "Quest Data loaded : {} starcount={}", file, quest.starcount);
    }
  }
}

void ModifyQuestNoList(void *obj) {
  auto file = (char *)obj + 0xc;
  if (std::string(file) != "quest\\questNoList") {
    return;
  }
  int *questCount = (int *)((char *)obj + 0xb8);
  int *capacity = (int *)((char *)obj + 0xbc);
  void ***questIds = (void ***)((char *)obj + 0xc8);

  log(INFO, "Overriding questNoList at {}. {} initial entries.", file, *questCount);
  increase_capacity((char *)obj + 0xb0, *capacity + AddedQuestCount);

  for (int i = 0; i < (int)AddedQuestCount; ++i) {
    void **nextQuestAddress = *questIds + i + *questCount;
    *nextQuestAddress = &AddedQuests[i].questNoListObj;
  }
  *questCount += (int)AddedQuestCount;
}

byte *get_call_func(byte *addr) {
  auto jump_addr = addr + 5; // size of call instruction
  auto offset = *reinterpret_cast<int *>(addr + 1);
  return jump_addr + offset;
}

void InjectQuestLoader() {
  auto is_master_rank_addr = find_func(sig::IS_MASTER_RANK);
  auto star_category_check_addr = find_func(sig::STAR_CATEGORY_CHECK);
  auto get_category_addr = find_func(sig::GET_CATEGORY);
  auto quest_checks_addr = find_func(sig::QUEST_CHECKS_FUNC);
  auto optional_checks_addr = find_func(sig::OPTIONAL_CHECKS_FUNC);
  auto increase_capacity_addr = find_func(sig::INCREASE_CAPACITY);
  auto load_quest_data_addr = find_func(sig::LOAD_QUEST_DATA);
  auto load_quest_no_list_addr = find_func(sig::LOAD_QUEST_NO_LIST);

  for (auto &opt : {
           is_master_rank_addr,
           star_category_check_addr,
           get_category_addr,
           quest_checks_addr,
           optional_checks_addr,
           increase_capacity_addr,
           load_quest_data_addr,
           load_quest_no_list_addr,
       }) {
    if (!opt) {
      return;
    }
  }

  increase_capacity = reinterpret_cast<void (*)(void *, uint32_t)>(*increase_capacity_addr);
  auto check_complete_addr = get_call_func(*quest_checks_addr + CHECK_COMPLETE_OFFSET);
  auto check_progress_addr = get_call_func(*quest_checks_addr + CHECK_PROGRESS_OFFSET);
  auto optional_count_addr = get_call_func(*optional_checks_addr + OPTIONAL_COUNT_OFFSETT);
  auto optional_at_addr = get_call_func(*optional_checks_addr + OPTIONAL_AT_OFFSET);

  log(INFO, "Hooking quest loader");
  PopulateQuests();

  MH_Initialize();
  Hook<bool(void *save, int id), line()>::hook(check_complete_addr, [](auto original, void *save, int id) {
    if (QuestExists(id)) {
      log(DEBUG, "CheckQuestLoader {}", id);
      return true;
    }
    return original(save, id);
  });

  Hook<bool(void *, int), line()>::hook(check_progress_addr, [](auto original, void *save, int id) {
    if (QuestExists(id)) {
      log(DEBUG, "CheckQuestProgress {}", id);
      return true;
    }
    return original(save, id);
  });

  Hook<int(int), line()>::hook(*is_master_rank_addr, [](auto original, int id) -> int {
    if (QuestExists(id)) {
      int starcount = QuestIds.at(id)->starcount;
      log(DEBUG, "IsMasterRank {} starcount:{}", id, starcount);
      return QuestIds.at(id)->starcount > 10;
    }
    return original(id);
  });

  auto optional_count_hook = Hook<int(), line()>{};
  optional_count_hook.hook(optional_count_addr, [](auto original) {
    log(DEBUG, "QuestCount");
    return original() + (int)AddedQuestCount;
  });

  Hook<int(void *, int), line()>::hook(optional_at_addr, [](auto original, void *this_ptr, int index) {
    if (index >= decltype(optional_count_hook)::orig()) {
      size_t newIndex = ((size_t)index) - decltype(optional_count_hook)::orig();
      log(DEBUG, "Optional at {} : {}", index, AddedQuests[newIndex].file_id);
      return (int)AddedQuests[newIndex].file_id;
    }
    return original(this_ptr, index);
  });

  Hook<bool(int, int, int), line()>::hook(*star_category_check_addr,
                                          [](auto original, int questID, int category, int starCount) {
    Quest *found;
    if (QuestExists(questID)) {
      found = GetQuest(questID);
      if (found->starcount == starCount && category == 1) {
        return true;
      }
    }
    return original(questID, category, starCount);
  });

  Hook<long long(int questID, int unkn), line()>::hook(*get_category_addr,
                                                       [](auto original, int questID, int unkn) -> long long {
    auto ret = original(questID, unkn);
    if (QuestExists(questID)) {
      log(DEBUG, "GetQuestCategory {}", questID);
      return 1;
    }
    return ret;
  });

  Hook<bool(void *, void *), line()>::hook(*load_quest_data_addr, [](auto orig, void *obj, void *stream) {
    bool ret = orig(obj, stream);
    ModifyQuestData(obj);
    return ret;
  });

  Hook<bool(void *, void *), line()>::hook(*load_quest_no_list_addr, [](auto orig, void *obj, void *stream) {
    bool ret = orig(obj, stream);
    ModifyQuestNoList(obj);
    return ret;
  });

  MH_ApplyQueued();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
  case DLL_PROCESS_ATTACH:
    InjectQuestLoader();
    break;
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
