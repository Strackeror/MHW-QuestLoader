// dllmain.cpp : Defines the entry point for the DLL application.

#include <filesystem>
#include <unordered_map>
#include "loader.h"
#include "scanmem.h"
#include "util.h"

using namespace loader;

const char* OPTIONAL_COUNT_BITS =
    "00110011 11...... 01001... 10001101 00...101 ........ ........ ........ "
    "........ 00001111 00011111 10000... 00000000 00000000 00000000 00000000 "
    "11111111 11000... 01001... 10001101 01...... ........ 10000011 00111... "
    "........ 01110101 ........ 11000011";

const char* STAR_CATEGORY_CHECK =
    "01001... 10001001 01...100 ..100... ........ 01001... 10001001 01...100 "
    "..100... ........ 01001... 10001001 01...100 ..100... ........ 01010... "
    "01001... 10000011 11101... ........ 01000... 10001011 11...... 10001011 "
    "11...... 10001011 11...... 10000011 11111... ........ 00001111 10000100 "
    "........ ........ ........ ........ 10000001 11111... ........ ........ "
    "........ ........ 01110101 ........ 01001... 10001011 00...101 ........ "
    "........ ........ ........ 00110011 11...... 11101000 ........ ........ "
    "........ ........ 10000100 11...... 00001111 10000100 ";

const char* IS_MASTER_RANK =
    "10001101 10...... ........ ........ ........ ........ 01000... 10001011 "
    "11...... 00111101 ........ ........ ........ ........ 00001111 10000111 "
    "........ ........ ........ ........ 01000... 10001011 11...... 10111... "
    "........ ........ ........ ........ 01000... 11110111 11101... 11000001 "
    "11111... ........ 10001011 11...... 11000001 11101... ........ 00000011 "
    "11...... 01101001 11...... ........ ........ ........ ........ 01000... "
    "00101011 11...... 10111... ........ ........ ........ ........ 01000... "
    "11110111 11101... 11000001 11111... ........ 10001011 11...... 11000001 "
    "11101... ........ 00000011 11...... 01101001 11...... ........ ........ "
    "........ ........ 00101011 11...... 10000001 11101... ........ ........ "
    "........ ........ 10000001 11111... ........ ........ ........ ........ "
    "01110011 ........ 10111... ........ ........ ........ ........ 01000... "
    "11110111 11101... 11000001 11111... ........ 10001011 11...... 11000001 "
    "11101... ........ 00000011 11...... 01101011 11...... ........ 01000... "
    "00101011 11...... 01000... 10001101 01...... ........ 10000011 11111... "
    "........ 00001111 10000010 ........ ........ ........ ........ 01000... "
    "10001101 01...... ........ 10000011 11111... ........ 00001111 10000010 "
    "........ ........ ........ ........ 00110011 11...... 11000011 01000... "
    "10001101 10...... ........ ........ ........ ........ 10000011 11111... "
    "........ 11101011 ........ 10001101 10...... ........ ........ ........ "
    "........ 00111101 ........ ........ ........ ........ 01110111 ........ "
    "10111... ........ ........ ........ ........ 01000... 11110111 11101... "
    "10001011 11...... 11000001 11111... ........ 10001011 11...... 11000001 "
    "11101... ........ 00000011 11...... 10111... ........ ........ ........ "
    "........ 11110111 11101... 11000001 11111... ........ 10001011 11...... "
    "11000001 11101... ........ 00000011 11...... 01101011 11...... ........ "
    "00101011 11...... 00110011 11...... 10000011 11111... ........ 00001111 "
    "10011101 11...... 11000011 10001101 10...... ........ ........ ........ "
    "........ 00111101 ........ ........ ........ ........ 01110111 ........ "
    "10111... ........ ........ ........ ........ 01000... 11110111 11101... "
    "11000001 11111... ........ 10001011 11...... 11000001 11101... ........ "
    "00000011 11...... 01101011 11...... ........ 01000... 00101011 11...... "
    "01000... 10000011 11111... ........ 01111101 ........ 00110011 11...... "
    "11000011 10001101 10...... ........ ........ ........ ........ 00111101 "
    "........ ........ ........ ........ 00001111 10000111 ........ ........ "
    "........ ........ 10111... ........ ........ ........ ........ 11000011";

const char* GET_CATEGORY =
    "10001101 10...... ........ ........ ........ ........ 10000011 11111... "
    "........ 01110111 ........ 10111... ........ ........ ........ ........ "
    "11000011 10000001 11111... ........ ........ ........ ........ 01110101 "
    "........ 10111... ........ ........ ........ ........ 11000011 10000001 "
    "11111... ........ ........ ........ ........ 01110101 ........ 10111... "
    "........ ........ ........ ........ 11000011 10000001 11111... ........ "
    "........ ........ ........ 00001111 10001101 ........ ........ ........ "
    "........ 10000001 11111... ........ ........ ........ ........ 01111100 "
    "........ 10111... ........ ........ ........ ........ 11000011 10000001 "
    "11111... ........ ........ ........ ........ 00001111 10001101 ........ "
    "........ ........ ........ 10000001 11111... ........ ........ ........ "
    "........ 01111100 ........ 10111... ........ ........ ........ ........ "
    "11110111 11101...";

const char* LOAD_RESOURCE =
    "01001... 10001001 01...100 ..100... ........ 01001... 10001001 01...100 "
    "..100... ........ 01001... 10001001 01...100 ..100... ........ 01001... "
    "10001001 01...100 ..100... ........ 01000... 01010... 01000... 01010... "
    "01000... 01010... 01001... 10000011 11101... ........ 10000000 10111... "
    "........ ........ ........ ........ ........ 01000... 10001011 11...... "
    "01001... 10001011 11...... 01001... 10001011 11...... 01001... 10001011 "
    "11...... 00001111 10000101 ........ ........ ........ ........ 01001... "
    "10000101 11...... 00001111 10000100 ........ ........ ........ ........";

const char* INCREASE_CAPACITY =
    "01001... 10001001 01...100 ..100... ........ 01001... 10001001 01...100 "
    "..100... ........ 01001... 10001001 01...100 ..100... ........ 01010... "
    "01001... 10000011 11101... ........ 01001... 10001011 11...... 10001011 "
    "11...... 01001... 10001101 00...101 ........ ........ ........ ........ "
    "11101000 ........ ........ ........ ........ 10001011 11...... 01000... "
    "10111... ........ ........ ........ ........ 01001... 11000001 11100... "
    "........ 01001... 10001011 11...... 01001... 10001011 11...... 01001... "
    "10001011 00...... 01000... 11111111 01010... ........ 01001... 10001011 "
    "11...... 00110011 11...... 01001... 10001011 11...... 01001... 10001011 "
    "11...... 11101000 ........ ........ ........ ........ 01000... 10001011 "
    "01...... ........ 01001... 10001011 11...... 01001... 10001011 01...... "
    "........ 01001... 11000001 11100... ........ 11101000 ........ ........ "
    "........ ........ 01001... 10001101 00...101 ........ ........ ........ "
    "........ 11101000 ........ ........ ........ ........ 01001... 10001011 "
    "01...... ........ 01001... 10001011 11...... 01001... 10001011 00...... "
    "01000... 11111111 01010... ........ 01001... 10001011 01...100 ..100... "
    "........ 10001001 01...... ........ 01001... 10001011 01...100 ..100... "
    "........ 01001... 10001001 01...... ........ 01001... 10001011 01...100 "
    "..100... ........ 01001... 10000011 11000... ........ 01011... 11000011";

const char* QUEST_CHECKS_FUNC =
    "01000... 01010... 01010... 01000... 01010... 01001... 10000011 11101... "
    "........ 01001... 10001011 11...... 01000... 00001111 10110110 11...... "
    "01001... 10000001 11000... ........ ........ ........ ........ 11101000 "
    "........ ........ ........ ........ 10000011 11111... ........ 00001111 "
    "10001110 ........ ........ ........ ........ 01001... 10001001 10...100 "
    "..100... ........ ........ ........ ........ 00110011 11...... 10001001 "
    "01...... ........ 01000... 10001000 01...... ........ 01000... 10001000 "
    "10...... ........ ........ ........ ........ 01100110 10001001 10...... "
    "........ ........ ........ ........ 01001... 11000111 01000... ........ "
    "........ ........ ........ ........ 01001... 01100011 10...... ........ "
    "........ ........ ........ 10000101 11...... 00001111 10001000 ........ "
    "........ ........ ........ 01001... 00111011 10...... ........ ........ "
    "........ ........ 00001111 10000011 ........ ........ ........ ........ "
    "01001... 10001011 10...100 ........ ........ ........ ........ ........ "
    "01001... 10001001 01...100 ..100... ........ 11101000 ........ ........ "
    "........ ........ 01001... 10001011 11...... 01001... 10000101 11...... "
    "00001111 10000100 ........ ........ ........ ........ 10001011 01...... "
    "........ 01001... 10001101 10...... ........ ........ ........ ........ "
    "10001001 01...... ........ 10001011 11...... 01000... 10001000 10...... "
    "........ ........ ........ ........ 00001111 10111110 01...... ........ "
    "10001001 01...... ........ 10001011 01...... ........ 10001001 01...... "
    "........ 01001... 10001001 10...100 ..100...";

const size_t CHECK_COMPLETE_OFFSET = 0x4e1;
const size_t CHECK_PROGRESS_OFFSET = 0x6d2;

const char* OPTIONAL_CHECKS_FUNC =
    "01001... 10000011 11101... ........ 01001... 10001011 00...101 ........ "
    "........ ........ ........ 11101000 ........ ........ ........ ........ "
    "01001... 10001011 11...... 11101000 ........ ........ ........ ........ "
    "00111101 ........ ........ ........ ........ 01110010 ........ 01001... "
    "10001011 00...101 ........ ........ ........ ........ 11101000 ........ "
    "........ ........ ........ 01001... 10001011 11...... 11101000 ........ "
    "........ ........ ........ 00111101 ........ ........ ........ ........ "
    "01110011 ........ 00110010 11...... 01001... 10000011 11000... ........ "
    "11000011 01001... 10001011 00...101 ........ ........ ........ ........ "
    "01001... 10001001 01...100 ..100... ........ 01001... 10001001 01...100 "
    "..100... ........ 01001... 10001001 01...100 ..100... ........ 11101000 "
    "........ ........ ........ ........ 01001... 10001011 11...... 11101000 "
    "........ ........ ........ ........ 00110011 11...... 10001011 11...... "
    "10000101 11...... 01111110 ........ 00001111 00011111 01000... 00000000 "
    "01001... 10001011 00...101 ........ ........ ........ ........ 11101000 "
    "........ ........ ........ ........ 01001... 10001011 11...... 10001011 "
    "11...... 11101000 ........ ........ ........ ........ 10001011 11...... "
    "10000011 11111... ........ 01110100 ........ 00110011 11...... 10001011 "
    "11...... 11101000 ........ ........ ........ ........ 10000011 11111... "
    "........ 01110101 ........ 01001... 10001011 00...101 ........ ........ "
    "........ ........ 11101000 ........ ........ ........ ........ 01001... "
    "10001011 11...... 10001011 11...... 11101000 ........ ........ ........ "
    "........ 10000100 11...... 01110101 ........ 11111111 11000... 00111011 "
    "11...... 01111100 ........ 01001... 10001011 01...100 ..100... ........ "
    "00110010 11...... 01001... 10001011 01...100 ..100... ........ 01001... "
    "10001011 01...100 ..100... ........ 01001... 10000011 11000... ........ "
    "11000011 01001... 10001011 01...100 ..100... ........ 10110... ........ "
    "01001... 10001011 01...100 ..100... ........ 01001... 10001011 01...100 "
    "..100... ........ 01001... 10000011 11000... ........ 11000011";

const size_t OPTIONAL_AT_OFFSET = 0x81;

static void (*increase_capacity)(void*, uint32_t) = nullptr;
static void* QuestDataResource = nullptr;
static void* QuestNoListResource = nullptr;

class Quest {
 public:
  int file_id;

  struct {
    void* vtable = nullptr;
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
std::unordered_map<int, Quest*> QuestIds;

static void PopulateQuests() {
  if (!std::filesystem::exists("nativePC\\quest"))
    return;
  for (auto& entry : std::filesystem::directory_iterator("nativePC\\quest")) {
    std::string name = entry.path().filename().string();
    if (entry.path().filename().extension().string() != ".mib")
      continue;

    int id;
    if (sscanf_s(name.c_str(), "questData_%d.mib", &id) != 1)
      continue;
    if (id < 90000)
      continue;

    LOG(WARN) << "Registered quest at " << entry.path().string();
    AddedQuests.push_back(Quest(id));
  }

  for (auto& quest : AddedQuests) {
    QuestIds.insert({quest.file_id, &quest});
  }
  AddedQuestCount = AddedQuests.size();
}

bool QuestExists(int id) {
  return QuestIds.count(id);
}

Quest* GetQuest(int id) {
  return QuestIds.find(id)->second;
}

void ModifyQuestData(void* obj, char* file) {
  for (auto& quest : AddedQuests) {
    if (quest.questPath == std::string(file)) {
      *(int*)((char*)obj + 0xb0 + 0x30) = (int)quest.file_id;
      quest.starcount = *offsetPtr<unsigned char>(obj, 0xb0 + 0x34);
      LOG(INFO) << "Quest Data loaded : " << file << " "
                << SHOW(quest.starcount);
    }
  }
}

void ModifyQuestNoList(void* obj, char* file) {
  int* questCount = (int*)((char*)obj + 0xb8);
  int* capacity = (int*)((char*)obj + 0xbc);
  void*** questIds = (void***)((char*)obj + 0xc8);

  LOG(INFO) << "Overriding questNoList. " << *questCount << " initial entries.";

  increase_capacity((char*)obj + 0xb0, *capacity + AddedQuestCount);

  for (int i = 0; i < (int)AddedQuestCount; ++i) {
    void** nextQuestAddress = *questIds + i + *questCount;
    *nextQuestAddress = &AddedQuests[i].questNoListObj;
  }
  *questCount += (int)AddedQuestCount;
}

std::optional<byte*> find_func(std::string_view binary) {
  auto [bytes, mask] = parseBinary(binary);
  auto found = scanmem(bytes, mask);
  if (found.size() != 1) {
    return {};
  }
  return found[0];
}

byte* get_call_func(byte* addr) {
  auto jump_addr = addr + 5;  // size of call instruction
  auto offset = *reinterpret_cast<int*>(addr + 1);
  return jump_addr + offset;
}

std::optional<byte*> get_resource_ptr(std::string_view name, int offset) {
  std::vector<byte> vec(name.size());
  for (int i = 0; i < name.size(); ++i) {
    vec[i] = name[i];
  }

  auto found = scanmem(vec);
  if (found.size() != 1) {
    LOG(ERR) << std::format("didn't find name {} in memory", name);
    return {};
  }

  auto string_addr = found[0];
  auto vtable_addr = string_addr + offset;
  auto func = *reinterpret_cast<byte**>(vtable_addr);
  auto instruction = func + 0xa;
  if (*instruction != 0x48) {
    LOG(ERR) << std::format("wrong instruction for {}", name);
    return {};
  }

  return (byte*)(instruction + *(uint32_t*)(instruction + 0x3) + 0x7);
}

void InjectQuestLoader() {
  auto is_master_rank_addr = find_func(IS_MASTER_RANK);
  auto optional_count_addr = find_func(OPTIONAL_COUNT_BITS);
  auto star_category_check_addr = find_func(STAR_CATEGORY_CHECK);
  auto get_category_addr = find_func(GET_CATEGORY);
  auto load_resource_addr = find_func(LOAD_RESOURCE);
  auto quest_checks_addr = find_func(QUEST_CHECKS_FUNC);
  auto optional_checks_addr = find_func(OPTIONAL_CHECKS_FUNC);
  auto increase_capacity_addr = find_func(INCREASE_CAPACITY);
  for (auto& opt :
       {is_master_rank_addr, optional_count_addr, star_category_check_addr,
        get_category_addr, load_resource_addr, quest_checks_addr,
        optional_checks_addr, increase_capacity_addr}) {
    if (!opt) {
      LOG(ERR) << "Failed to find a function";
      return;
    }
  }

  auto quest_data = get_resource_ptr("rQuestData", -0x58);
  auto quest_no_list = get_resource_ptr("rQuestNoList", -0x18);
  

  if (!quest_data || !quest_no_list) {
    LOG(ERR) << "Failed to find a resource ptr";
    return;
  }

  QuestDataResource = *quest_data;
  QuestNoListResource = *quest_no_list;

  increase_capacity =
      reinterpret_cast<void (*)(void*, uint32_t)>(*increase_capacity_addr);
  auto check_complete_addr =
      get_call_func(*quest_checks_addr + CHECK_COMPLETE_OFFSET);
  auto check_progress_addr =
      get_call_func(*quest_checks_addr + CHECK_PROGRESS_OFFSET);
  auto optional_at = get_call_func(*optional_checks_addr + OPTIONAL_AT_OFFSET);
  
  LOG(INFO) << SHOW((void*)*is_master_rank_addr);
  LOG(INFO) << SHOW((void*)*optional_count_addr);
  LOG(INFO) << SHOW((void*)*star_category_check_addr);
  LOG(INFO) << SHOW((void*)*get_category_addr);
  LOG(INFO) << SHOW((void*)*load_resource_addr);
  LOG(INFO) << SHOW((void*)*increase_capacity_addr);
  LOG(INFO) << SHOW((void*)*quest_data);
  LOG(INFO) << SHOW((void*)*quest_no_list);
  LOG(INFO) << SHOW((void*)check_complete_addr);
  LOG(INFO) << SHOW((void*)check_progress_addr);
  LOG(INFO) << SHOW((void*)optional_at);

  LOG(WARN) << "Hooking Quest Loader";
  PopulateQuests();

  MH_Initialize();
  Hook<bool(void* save, int id), line()>::hook(
      check_complete_addr, [](auto original, void* save, int id) {
        {
          if (QuestExists(id)) {
            LOG(DEBUG) << "CheckQuestComplete : " << id;
            return true;
          }
          return original(save, id);
        }
      });

  Hook<bool(void* save, int id), line()>::hook(
      check_progress_addr, [](auto original, void* save, int id) {
        {
          if (QuestExists(id)) {
            LOG(DEBUG) << "CheckQuestProgress: " << id;
            return true;
          }
          return original(save, id);
        }
      });

  Hook<int(int id), line()>::hook(*is_master_rank_addr, [](auto original, int id) -> int{
    {
      if (QuestExists(id)) {
        int starcount = QuestIds.at(id)->starcount;
        LOG(DEBUG) << "IsMasterRank" << SHOW(starcount);
        return QuestIds.at(id)->starcount > 10;
      }
      return original(id);
    }
  });

  auto optional_count_hook = Hook<int(), line()>{};
  optional_count_hook.hook(*optional_count_addr, [](auto original) {
    {
      LOG(DEBUG) << "QuestCount";
      return original() + (int)AddedQuestCount;
    }
  });

  Hook<int(void* this_ptr, int index), line()>::hook(
      optional_at, [](auto original, void* this_ptr, int index) {
        {
          if (index >= decltype(optional_count_hook)::orig()) {
            size_t newIndex =
                ((size_t)index) - decltype(optional_count_hook)::orig();
            LOG(DEBUG) << "QuestFromIndex :" << index << ":"
                       << AddedQuests[newIndex].file_id;
            return (int)AddedQuests[newIndex].file_id;
          }
          return original(this_ptr, index);
        }
      });

  Hook<bool(int questID, int category, int starCount), line()>::hook(
      *star_category_check_addr,
      [](auto original, int questID, int category, int starCount) {
        {
          Quest* found;
          if (QuestExists(questID)) {
            found = GetQuest(questID);
            if (found->starcount == starCount && category == 1) {
              return true;
            }
          }
          return original(questID, category, starCount);
        }
      });

  Hook<long long(int questID, int unkn), line()>::hook(
      *get_category_addr,
      [](auto original, int questID, int unkn) -> long long {
        {
          auto ret = original(questID, unkn);
          if (QuestExists(questID)) {
            LOG(DEBUG) << "GetQuestCategory " << questID;
            return 1;
          }
          return ret;
        }
      });

  Hook<void*(void* fileMgr, void* objDef, char* filename, int flag), line()>::hook(
      *load_resource_addr,
      [](auto original, void* fileMgr, void* objDef, char* filename, int flag) {
        {
          void* object = original(fileMgr, objDef, filename, flag);

          if (flag == 1) {
            if (objDef == QuestDataResource) {
              ModifyQuestData(object, filename);
            }
            if (objDef == QuestNoListResource &&
                filename == std::string("quest\\questNoList")) {
              ModifyQuestNoList(object, filename);
            }
          }
          return object;
        }
      });

  MH_ApplyQueued();
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
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
