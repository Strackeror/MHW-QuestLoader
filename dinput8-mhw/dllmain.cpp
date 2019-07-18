// dllmain.cpp : Defines the entry point for the DLL application.
#include <SDKDDKVer.h>
#include <windows.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <sstream>

#include "MinHook.h"
#include "log.h"

typedef HRESULT(WINAPI* tDirectInput8Create)(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk);
tDirectInput8Create oDirectInput8Create = nullptr;

#define HOOKFUNC(NAME, RET, ...) typedef RET (__fastcall*  t ## NAME)( __VA_ARGS__); \
t##NAME original##NAME; \
RET __fastcall NAME(__VA_ARGS__)

#define AddHook(NAME, OFFSET) do {MH_CreateHook((void*)OFFSET, & NAME, (LPVOID *)& original##NAME); MH_EnableHook((void *)OFFSET);} while(0)

class Quest {
public:
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

HOOKFUNC(CheckQuestUnlocked, bool, void* this_ptr, int id)
{
	LOG(INFO) << "QuestUnlocked : " << id;
	for (auto quest : Quest::Quests)
	{
		if (quest.file_id == id) {
			return true;
		}
	}
	return originalCheckQuestUnlocked(this_ptr, id);
}


HOOKFUNC(CheckQuestProgress, bool, void* this_ptr, int index)
{
	LOG(INFO) << "CheckQuestProgress " << index;
	if (index > 90000) {
		return true;
	}
	return originalCheckQuestProgress(this_ptr, index);
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
	for (auto quest : Quest::Quests)
	{
		if (questID != quest.file_id) continue;
		if (category == 1 && starCount == quest.starcount) return true;
		return false;
	}
	return ret;
}

HOOKFUNC(GetQuestCategory, long long, int questID, int unkn)
{
	LOG(INFO) << "GetQuestCategory";
	auto ret = originalGetQuestCategory(questID, unkn);
	if (questID > 90000) {
		return 1;
	}
	return ret;
}

HOOKFUNC(LoadFilePath, void*, void* this_ptr, void* loaderPtr, char* path, int flag)
{
	LOG(INFO) << "Loadfile:" << path;
	void* ret = originalLoadFilePath(this_ptr, loaderPtr, path, flag);

	if (loaderPtr == (void*)0x143be40d8)
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

/*
typedef void(__fastcall* tGetMonsterString)(char* buf, size_t size, unsigned int id);
tGetMonsterString originalGetString;

void __fastcall GetMonsterString(char *buf, size_t size, unsigned int id)
{
	LOG(INFO) << "MonsterString ";
	originalGetString(buf, size, id % 256);
	if (id >= 256) 
	{
		id = id >> 16;
		sprintf_s(buf + 6, size - 6, "%02d", id);
		LOG(INFO) << "mod variant called:" << id << " return value : " << buf;
	}
}
*/


static int next_id = 0;
HOOKFUNC(CreateMonster, void, void* this_ptr, void* unkn, void* ptr, char flag)
{
	int monster_id = *(int*)((char*)this_ptr + 0x158);
	unsigned int subspecies_override = *(int*)((char*)this_ptr + 0x10c);
	if (subspecies_override == 0xCDCDCDCD) 
		subspecies_override = 0;
	else
		next_id = subspecies_override;

	LOG(WARN) << "Creating Monster : " << monster_id
		 << ":" << subspecies_override << " flags " << (int)flag;
	return originalCreateMonster(this_ptr, unkn, ptr, flag);
}

HOOKFUNC(ConstructMonster, void*, void* this_ptr, unsigned int monster_id, unsigned int variant)
{
	if (next_id) {
		LOG(INFO) << "Setting Subspecies :" << next_id;
		variant = next_id;
		next_id = 0;
	}
	return originalConstructMonster(this_ptr, monster_id, variant);
}


/// Test Hooks for logging shit

HOOKFUNC(SetMonsterAnim, void*, void* this_ptr, unsigned int animationID, void* _1, void* _2)
{
	LOG(WARN) << "Monster PTR: " << this_ptr << " -  Action ID:" << std::hex << animationID << std::dec;
	return originalSetMonsterAnim(this_ptr, animationID, _1, _2);
}


void Initialize()
{
	char syspath[MAX_PATH];
	GetSystemDirectory(syspath, MAX_PATH);
	strcat_s(syspath, "\\dinput8.dll");
	HMODULE hMod = LoadLibrary(syspath);
	oDirectInput8Create = (tDirectInput8Create)GetProcAddress(hMod, "DirectInput8Create");

	Quest::PopulateQuests();


	LOG(WARN) << "Hooking";
	MH_Initialize();

	// Quest Hooks
	AddHook(QuestCount, 0x148954df0);
	AddHook(QuestFromIndex, 0x148954e80);
	AddHook(CheckQuestProgress, 0x148954d70);
	AddHook(CheckQuestUnlocked, 0x1489548c0);

	AddHook(CheckStarAndCategory, 0x1474d0ae0);
	AddHook(GetQuestCategory, 0x14e0829d0);
	AddHook(LoadFilePath, 0x1506cf8f0);


	// Subspecies Hooks
	AddHook(CreateMonster, 0x14e61aff0);
	AddHook(ConstructMonster, 0x14f11f9c0);


	// Test hooks
	//AddHook(SetMonsterAnim, 0x14bd3b600);


	LOG(WARN) << "Hooking OK";


}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{

#ifndef _DEBUG
	min_log_level = ERR;
#else
	min_log_level = WARN;
#endif // !_DEBUG
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		Initialize();
	}
	return TRUE;
}

HRESULT WINAPI DirectInput8Create(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk)
{
	return oDirectInput8Create(inst_handle, version, r_iid, out_wrapper, p_unk);
}
