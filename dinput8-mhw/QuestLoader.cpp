#include "loader.h"
#include "dll.h"
#include "ghidra_export.h"

using namespace loader;

class Quest {
public:
	long long file_id;

	struct {
		void* vtable = nullptr;
		long long questId;

		char stuff[0x50];
	} questNoListObj;

	int starcount = 10;
	std::string questPath;

	Quest(int id) : file_id(id) 
	{
		char buf[250];
		sprintf_s(buf, "quest\\questData_%05d", id);
		questPath = buf;

		questNoListObj.questId = id;
	}
};

static const int	QuestMinId = 90000;
size_t				AddedQuestCount;
std::vector<Quest>	AddedQuests;

static void PopulateQuests() 
{
	if (!std::filesystem::exists("nativePC\\quest"))
		return;
	for (auto& entry : std::filesystem::directory_iterator("nativePC\\quest"))
	{
		std::string name = entry.path().filename().string();
		if (entry.path().filename().extension().string() != ".mib") continue;

		int id;
		if (sscanf_s(name.c_str(), "questData_%d.mib", &id) != 1) continue;
		if (id < 90000) continue;

		LOG(WARN) << "Registered quest at " << entry.path().string();
		AddedQuests.push_back(Quest(id));
	}
	AddedQuestCount = AddedQuests.size();
}


CreateHook(MH::Quest::CheckComplete, CheckQuestComplete, bool, void* save, int id)
{
	if (id >= QuestMinId)
	{
		LOG(INFO) << "CheckQuestComplete : " << id;
		return true;
	}
	return original(save, id);
}

CreateHook(MH::Quest::CheckProgress, CheckQuestProgress, bool, void* save, int id)
{
	if (id >= QuestMinId)
	{
		LOG(INFO) << "CheckQuestProgress: " << id;
		return true;
	}
	return original(save, id);
}

CreateHook(MH::Quest::UnknFilterFlag, CheckQuestFlag, bool, int id)
{
	if (id >= QuestMinId)
	{
		LOG(INFO) << "CheckQuestFlag : " << id;
		return true;
	}
	return original(id);
}


CreateHook(MH::Quest::OptionalCount, QuestCount, int, void)
{
	LOG(INFO) << "QuestCount";
	return original() + (int) AddedQuestCount;
}

CreateHook(MH::Quest::OptionalAt, QuestFromIndex, int, void* this_ptr, int index)
{
	if (index >= QuestCount::original())
	{
		LOG(INFO) << "QuestFromIndex :" << index << ":" << AddedQuests[(long long) index - QuestCount::original()].file_id;
		return (int) AddedQuests[(long long) index - QuestCount::original()].file_id;
	}
	return original(this_ptr, index);
}

CreateHook(MH::Quest::StarCategoryCheck, CheckStarAndCategory, bool, int questID, int category, int starCount)
{
	auto ret = original(questID, category, starCount);
	if (questID >= QuestMinId && category == 1 && starCount == 16)
	{
		LOG(INFO) << "CheckStarCategory " << questID;
		return true;
	}
	return ret;
}

CreateHook(MH::Quest::GetCategory, GetQuestCategory, long long, int questID, int unkn)
{
	auto ret = original(questID, unkn);
	if (questID >= QuestMinId) {
		LOG(DEBUG) << "GetQuestCategory " << questID;
		return 1;
	}
	return ret;
}

void ModifyQuestData(void* obj, char* file)
{
	for (auto& quest : AddedQuests)
	{
		if (quest.questPath == std::string(file))
		{
			LOG(INFO) << "Quest Data loaded : " << file;
			*(int*)((char*)obj + 0xb0 + 0x70) = (int) quest.file_id;
		}
	}
}


void ModifyQuestNoList(void* obj, char* file)
{
	int* questCount = (int*)((char*)obj + 0xb8);
	int* capacity =	(int*)((char*)obj + 0xbc);
	void*** questIds = (void***)((char*)obj + 0xc8);

	LOG(INFO) << "Overriding questNoList. " << *questCount << " initial entries.";

	MH::List::IncreaseCapacity((char*)obj + 0xb0, *capacity + AddedQuestCount);

	for (int i = 0; i < (int) AddedQuestCount; ++i)
	{
		void** nextQuestAddress = *questIds + i + *questCount;
		*nextQuestAddress =  &AddedQuests[i].questNoListObj;
	}
	*questCount += (int) AddedQuestCount;
}

CreateHook(MH::File::LoadResource, LoadObjFile, void*, void* fileMgr, void* objDef, char* filename, int flag)
{
	void* object = original(fileMgr, objDef, filename, flag);

	if (flag == 1)
	{
		if (objDef == MH::Quest::QuestData::ResourcePtr)
			ModifyQuestData(object, filename);
		if (objDef == MH::Quest::QuestNoList::ResourcePtr)
			ModifyQuestNoList(object, filename);
	}
	return object;
}

void InjectQuestLoader()
{
	if (!ConfigFile.value("enableQuestLoader", true)) return;

	LOG(WARN) << "Hooking Quest Loader";
	PopulateQuests();

	QueueHook(QuestCount);
	QueueHook(QuestFromIndex);

	QueueHook(CheckQuestFlag);
	QueueHook(CheckQuestComplete);
	QueueHook(CheckQuestProgress);

	QueueHook(GetQuestCategory);
	QueueHook(CheckStarAndCategory);

	QueueHook(LoadObjFile);
}

