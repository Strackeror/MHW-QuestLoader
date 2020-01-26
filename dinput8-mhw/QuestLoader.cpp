#include "log.h"
#include "dll.h"

// UI Filter Function
// 44 89 44 24 18 41 54 41 57 48 83 ec 58 41 89 d4 49 89 cf 83 fa 02
/*
	  if (0 < iVar5) {
		puVar20 = (uint *)(param_1 + 0x3f70);
		do {
		  uStack112 = 0x15375157e;
		  lVar14 = List:GetIndex(_QuestManager,(ulonglong)uVar3);
		  if ((lVar14 != 0) && (uVar1 = *(uint *)(lVar14 + 8), uVar1 != 0)) {
			uStack112 = 0x153751596;
			uVar12 = Quest:GetQuestManager?(_DAT_144d34720);
			uStack112 = 0x1537515a0;
			uVar12 = Quest:CheckComplete(uVar12,(ulonglong)uVar1);
			if ((char)uVar12 == '\0') {
			  uStack112 = 0x1537515b6;
			  cVar2 = Quest:CheckStarAndCategory((ulonglong)uVar1,local_res8,(ulonglong)param_3);
			  if (cVar2 != '\0') {
				uStack112 = 0x1537515c1;
				iVar8 = Quest:CheckUnlock((ulonglong)uVar1);
*/
#define UIFilterCheckAddress			0x1537513e0
#define QuestCheckCompleteAddress		0x153eb38e0
#define	QuestStarCategoryAddress		0x152ed7330
#define QuestCheckUnlockAddress			0x156837d70

// First function call in QuestCheckComplete
#define QuestCategoryAddress			0x156835910		


// ff c0 48 8d 49 04 83 39 ff 75 f5 c3
// SUBSTRACT 0x10
#define QuestCountAddress				0x153ecdcc0

// 48 63 c2 ?????????????? 8b 04 81 c3
#define QuestNoFromIndexAddress			0x153ecdae0	

// 48 83 ec 30 80 b9 7b 80 20 00 00
// SUBSTRACT 0x1a
#define LoadObjFromFileAddress			0x160adf1e0



// Search for string 'rQuestData'
// Follow pointer 0x58 bytes before that string
// Address loaded in RCX at 0xA bytes in function pointed
// (First parameter of first function call)
#define QuestDataObjDefAddress			0x144d2c908

// Search for string 'rQuestNoList'
// Follow pointer 0x18 bytes before that string
// Address loaded in RCX at 0xA bytes in function pointed
#define QuestNoListObjDefAddress		0x1449e8dd0

class Quest {
public:
	static const int QuestMinId = 90000;
	static std::vector<Quest> Quests;
	static int size;


	
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

size_t				AddedQuestCount;
std::vector<Quest>	AddedQuests;

static void PopulateQuests() 
{
	if (!std::filesystem::exists("nativePC/quest"))
		return;
	for (auto& entry : std::filesystem::directory_iterator("nativePC/quest"))
	{
		std::string name = entry.path().filename().string();
		if (entry.path().filename().extension().string() != ".mib") continue;

		int id;
		if (sscanf_s(name.c_str(), "questData_%d.mib", &id) != 1) continue;
		if (id < 90000) continue;

		LOG(WARN) << "found quest: " << id;
		AddedQuests.push_back(Quest(id));
	}
	AddedQuestCount = AddedQuests.size();
}


HOOKFUNC(CheckQuestComplete, bool, void* this_ptr, int id)
{
	if (id >= Quest::QuestMinId)
	{
		LOG(INFO) << "CheckQuestComplete : " << id;
		return true;
	}
	return originalCheckQuestComplete(this_ptr, id);
}

HOOKFUNC(CheckQuestUnlock, bool, int id)
{
	if (id >= Quest::QuestMinId)
	{
		LOG(INFO) << "CheckQuestUnlock : " << id;
		return true;
	}
	return originalCheckQuestUnlock(id);
}

HOOKFUNC(QuestCount, int, void)
{
	LOG(INFO) << "QuestCount";
	return originalQuestCount() + (int) AddedQuestCount;
}

HOOKFUNC(QuestFromIndex, int, void* this_ptr, int index)
{
	if (index >= originalQuestCount())
	{
		LOG(INFO) << "QuestFromIndex :" << index << ":" << AddedQuests[index - originalQuestCount()].file_id;
		return (int) AddedQuests[index - originalQuestCount()].file_id;
	}
	return originalQuestFromIndex(this_ptr, index);
}

HOOKFUNC(CheckStarAndCategory, bool, int questID, int category, int starCount)
{
	auto ret = originalCheckStarAndCategory(questID, category, starCount);
	if (questID >= Quest::QuestMinId && category == 1 && starCount == 16)
	{
		LOG(INFO) << "CheckStarCategory " << questID;
		return true;
	}
	return ret;
}

HOOKFUNC(GetQuestCategory, long long, int questID, int unkn)
{
	auto ret = originalGetQuestCategory(questID, unkn);
	if (questID >= Quest::QuestMinId) {
		LOG(INFO) << "GetQuestCategory " << questID;
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
	void*** questIds = (void***)((char*)obj + 0xc8);

	LOG(INFO) << "Overriding questNoList. " << *questCount << "initial entries.";

	for (int i = 0; i < (int) AddedQuestCount; ++i)
	{
		void** nextQuestAddress = *questIds + i + *questCount;
		*nextQuestAddress =  &AddedQuests[i].questNoListObj;
	}
	*questCount += (int) AddedQuestCount;
}

HOOKFUNC(LoadObjFile, void*, void* fileMgr, void* objDef, char* filename, int flag)
{
	void* object = originalLoadObjFile(fileMgr, objDef, filename, flag);

	if (flag == 1)
	{
		switch ((long long)objDef)
		{
		case QuestDataObjDefAddress:
			ModifyQuestData(object, filename);
			break;
		case QuestNoListObjDefAddress:
			ModifyQuestNoList(object, filename);
			break;
		}
	}
	return object;
}

void InjectQuestLoader()
{
	PopulateQuests();
	LOG(WARN) << "Hooking Quest Loader";

	AddHook(QuestCount, QuestCountAddress);
	AddHook(QuestFromIndex, QuestNoFromIndexAddress);

	AddHook(CheckQuestUnlock, QuestCheckUnlockAddress);
	AddHook(CheckQuestComplete, QuestCheckCompleteAddress);

	AddHook(GetQuestCategory, QuestCategoryAddress);
	AddHook(CheckStarAndCategory, QuestStarCategoryAddress);

	AddHook(LoadObjFile, LoadObjFromFileAddress);
}

