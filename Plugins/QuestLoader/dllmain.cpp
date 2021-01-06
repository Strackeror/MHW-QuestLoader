// dllmain.cpp : Defines the entry point for the DLL application.

#include <map>
#include <unordered_map>

#include <filesystem>

#include "loader.h"
#include "util.h"
#include "ghidra_export.h"

using namespace loader;

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
  if (!std::filesystem::exists("nativePC\\quest")) return;
  for (auto& entry : std::filesystem::directory_iterator("nativePC\\quest")) {
    std::string name = entry.path().filename().string();
    if (entry.path().filename().extension().string() != ".mib") continue;

    int id;
    if (sscanf_s(name.c_str(), "questData_%d.mib", &id) != 1) continue;
    if (id < 90000) continue;

    LOG(WARN) << "Registered quest at " << entry.path().string();
    AddedQuests.push_back(Quest(id));
  }

  for (auto& quest : AddedQuests) {
    QuestIds.insert({quest.file_id, &quest});
  }
  AddedQuestCount = AddedQuests.size();
}

bool QuestExists(int id) { return QuestIds.find(id) != QuestIds.end(); }

Quest* GetQuest(int id) { return QuestIds.find(id)->second; }

CreateHook(MH::Quest::CheckComplete, CheckQuestComplete, bool, void* save,
           int id) {
  if (QuestExists(id)) {
    LOG(INFO) << "CheckQuestComplete : " << id;
    return true;
  }
  return original(save, id);
}

CreateHook(MH::Quest::CheckProgress, CheckQuestProgress, bool, void* save,
           int id) {
  if (QuestExists(id)) {
    LOG(INFO) << "CheckQuestProgress: " << id;
    return true;
  }
  return original(save, id);
}

CreateHook(MH::Quest::IsMasterRank, IsMasterRank, int, int id) {
  if (QuestExists(id)) {
    int starcount = QuestIds.at(id)->starcount;
    LOG(INFO) << "IsMasterRank" << SHOW(starcount);
    return QuestIds.at(id)->starcount > 10;
  }
  return original(id);
}

CreateHook(MH::Quest::OptionalCount, QuestCount, int, void) {
  LOG(DEBUG) << "QuestCount";
  return original() + (int)AddedQuestCount;
}

CreateHook(MH::Quest::OptionalAt, QuestFromIndex, int, void* this_ptr,
           int index) {
  if (index >= QuestCount::original()) {
    size_t newIndex = ((size_t)index) - QuestCount::original();
    LOG(DEBUG) << "QuestFromIndex :" << index << ":"
               << AddedQuests[newIndex].file_id;
    return (int)AddedQuests[newIndex].file_id;
  }
  return original(this_ptr, index);
}

CreateHook(MH::Quest::StarCategoryCheck, CheckStarAndCategory, bool,
           int questID, int category, int starCount) {
  auto ret = original(questID, category, starCount);
  Quest* found;
  if (QuestExists(questID)) {
    found = GetQuest(questID);
    LOG(DEBUG) << "CheckStarCategory" << SHOW(questID)
               << SHOW(found->starcount);
    if (found->starcount == starCount && category == 1) {
      return true;
    }
  }
  return ret;
}

CreateHook(MH::Quest::GetCategory, GetQuestCategory, long long, int questID,
           int unkn) {
  auto ret = original(questID, unkn);
  if (QuestExists(questID)) {
    LOG(DEBUG) << "GetQuestCategory " << questID;
    return 1;
  }
  return ret;
}

void ModifyQuestData(void* obj, char* file) {
  for (auto& quest : AddedQuests) {
    if (quest.questPath == std::string(file)) {
      *(int*)((char*)obj + 0xb0 + 0x70) = (int)quest.file_id;
      quest.starcount = *offsetPtr<unsigned char>(obj, 0xb0 + 0x74);
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

  MH::List::IncreaseCapacity((char*)obj + 0xb0, *capacity + AddedQuestCount);

  for (int i = 0; i < (int)AddedQuestCount; ++i) {
    void** nextQuestAddress = *questIds + i + *questCount;
    *nextQuestAddress = &AddedQuests[i].questNoListObj;
  }
  *questCount += (int)AddedQuestCount;
}

CreateHook(MH::File::LoadResource, LoadObjFile, void*, void* fileMgr,
           void* objDef, char* filename, int flag) {
  void* object = original(fileMgr, objDef, filename, flag);

  if (flag == 1) {
    if (objDef == MH::Quest::QuestData::ResourcePtr)
      ModifyQuestData(object, filename);
    if (objDef == MH::Quest::QuestNoList::ResourcePtr)
      ModifyQuestNoList(object, filename);
  }
  return object;
}

void InjectQuestLoader() {
  if (loader::GameVersion != std::string("421470")) {
    LOG(ERR) << "Quest Loader : Wrong version, please update the loader";
  }

  LOG(WARN) << "Hooking Quest Loader";
  PopulateQuests();

  MH_Initialize();

  QueueHook(QuestCount);
  QueueHook(QuestFromIndex);

  QueueHook(IsMasterRank);
  QueueHook(CheckQuestComplete);
  QueueHook(CheckQuestProgress);

  QueueHook(GetQuestCategory);
  QueueHook(CheckStarAndCategory);

  QueueHook(LoadObjFile);

  MH_ApplyQueued();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
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

