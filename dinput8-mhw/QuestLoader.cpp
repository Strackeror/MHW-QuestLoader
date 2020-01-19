#include "log.h"
#include "dll.h"

class Quest {
public:
	static const int QuestMinId = 90000;
	static std::vector<Quest> Quests;
	static int size;
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
			Quests.push_back(Quest(id));
		}
		size = Quest::Quests.size();
	}


	int file_id;
	int starcount = 10;
	std::string questPath;

	Quest(int id) : file_id(id) 
	{
		char buf[250];
		sprintf_s(buf, "quest\\questData_%05d", id);
		questPath = buf;
	}
};

std::vector<Quest> Quest::Quests;
int Quest::size;

HOOKFUNC(CheckQuestAvailable0, bool, void* this_ptr, int id)
{
	LOG(INFO) << "CheckQuestAvailable0 : " << id;
	if (id >= Quest::QuestMinId)
		return true;
	return originalCheckQuestAvailable0(this_ptr, id);
}

HOOKFUNC(CheckQuestAvailable1, bool, void* this_ptr, int id)
{
	LOG(INFO) << "CheckQuestAvailable1 : " << id;
	if (id >= Quest::QuestMinId)
		return true;
	return originalCheckQuestAvailable1(this_ptr, id);
}


HOOKFUNC(CheckQuestAvailable2, bool, void* this_ptr, int id)
{
	LOG(INFO) << "CheckQuestAvailable2 : " << id;
	if (id >= Quest::QuestMinId)
		return true;
	return originalCheckQuestAvailable2(this_ptr, id);
}

HOOKFUNC(CheckQuestUnlock, bool, void* this_ptr, int id)
{
	LOG(INFO) << "CheckQuestUnlock : " << id;
	if (id >= Quest::QuestMinId)
		return true;
	return originalCheckQuestUnlock(this_ptr, id);
}

HOOKFUNC(QuestCount, int, void)
{
	LOG(INFO) << "QuestCount";
	return originalQuestCount() + Quest::size;
}

HOOKFUNC(QuestFromIndex, int, void* this_ptr, int index)
{
	if (index >= originalQuestCount())
	{
		LOG(INFO) << "QuestFromIndex :" << index << ":" << Quest::Quests[index - originalQuestCount()].file_id;
		return Quest::Quests[index - originalQuestCount()].file_id;
	}
	return originalQuestFromIndex(this_ptr, index);
}

HOOKFUNC(CheckStarAndCategory, bool, int questID, int category, int starCount)
{
	LOG(INFO) << "CheckStarCategory " << questID;
	auto ret = originalCheckStarAndCategory(questID, category, starCount);
	if (questID >= Quest::QuestMinId && category == 1 && starCount == 10)
		return true;
	return ret;
}

HOOKFUNC(GetQuestCategory, long long, int questID, int unkn)
{
	LOG(INFO) << "GetQuestCategory";
	auto ret = originalGetQuestCategory(questID, unkn);
	if (questID >= Quest::QuestMinId) {
		return 1;
	}
	return ret;
}

HOOKFUNC(LoadFilePath, void*, void* this_ptr, void* loaderPtr, char* path, int flag)
{
	LOG(INFO) << "Loadfile:" << path;
	void* ret = originalLoadFilePath(this_ptr, loaderPtr, path, flag);

	// 40 53 41 56 48 81 ec d8 00 00 00 80 79 6c 00 48 89 cb 75 10 Load quest function
	// find this snippet :
	/*
		  thunk_FUN_145cf7570(local_68,"quest\\questData_%05d",1);
		  thunk_FUN_145cf7570(local_b8,"common\\text\\quest\\q%05d_jpn",1);
		  FUN_141e4dfb0(DAT_1448e0440,local_b8,local_b8,0);
		  cVar2 = thunk_FUN_150042c70(local_68,&DAT_143be79f8 <- THIS ADDRESS HERE);
	*/


	if (loaderPtr == (void*)0x143be79f8)
	{
		for (auto quest : Quest::Quests) 
		{
			if (quest.questPath == path) {
				*(int*)((char*)ret + 0xa8 + 0x70) = quest.file_id;
				LOG(WARN) << "Overrode id to " << quest.file_id << " in path " << path;
			}
		}
	}
	return ret;
}
void InjectQuestLoader()
{
	// UI Function offset checked here
	unsigned char* checkAddr = (unsigned char*)0x14b5fa080;
	if (checkAddr[0] != 0x48 ||
		checkAddr[1] != 0x89 ||
		checkAddr[2] != 0x5c)
	{
		LOG(ERR) << "Quest Loader Error : ";
		LOG(ERR) << "Safety check failed. Wrong monster hunter version.";
		LOG(ERR) << "Launching the game without patching.";
		LOG(ERR) << "Remove dinput8.dll to prevent this message from appearing at game start.";
		return;
	}


	Quest::PopulateQuests();


	LOG(WARN) << "Hooking";

	// UI Function
	// 48 89 5c 24 20 44 89 44 24 18 89 54 24 10 48 89 4c 24 08 55 56 57 41 54 41 55 41 56 41 57 48 83 ec 20 48 89 cd 31 f6
	/*
		uVar5 = thunk_FUN_14b7cdb70(DAT_143bebdd8);
		uVar4 = Quest.GetFromIndex(uVar5);
		lVar6 = thunk_FUN_14b7cdb70(DAT_143bebdd8);
		bVar1 = Quest.CheckUnlock(lVar6, uVar4);
		if ((bVar1 == false) &&
			(cVar2 = Quest.CheckStarAndCategory((ulonglong)uVar4, (ulonglong)param_2, (ulonglong)param_3)
				, cVar2 == '\x01')) {
	*/

	// Quest Hooks
	AddHook(QuestCount, 0x14be0a750); // 83 39 ff 75 f5 c3 (- 0x16 bytes)
	AddHook(QuestFromIndex, 0x14be0a7a0); // In UI Function

	// 48 89 5c 24 08 57 48 83 ec 20 89 d3 48 89 cf 89 d9 31 d2 - 4 results
	AddHook(CheckQuestAvailable0, 0x14be0a660);
	AddHook(CheckQuestAvailable1, 0x14be0a430);
	AddHook(CheckQuestAvailable2, 0x14be0a2d0);
	AddHook(CheckQuestUnlock, 0x14be0a250);

	// first func called in check progress and check unlocked
	AddHook(GetQuestCategory, 0x14e622860);

	// In UI function
	AddHook(CheckStarAndCategory, 0x14ae1d950);

	// 40 53 56 41 54 41 57 48 81 ec a8 04 00 00 45 89 cc 4c 89 c3 49 89 d7 48 89 ce 4d 85 c0
	AddHook(LoadFilePath, 0x1509d1aa0);


	LOG(WARN) << "Hooking OK";

}


