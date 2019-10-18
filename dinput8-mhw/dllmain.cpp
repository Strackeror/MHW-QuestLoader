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

HOOKFUNC(CheckQuestUnlocked, bool, void* this_ptr, int id)
{
	LOG(INFO) << "QuestUnlocked : " << id;
	if (id >= Quest::QuestMinId)
		return true;
	return originalCheckQuestUnlocked(this_ptr, id);
}


HOOKFUNC(CheckQuestProgress, bool, void* this_ptr, int id)
{
	LOG(INFO) << "CheckQuestProgress " << id;
	if (id >= Quest::QuestMinId)
		return true;
	return originalCheckQuestProgress(this_ptr, id);
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
	// Find function call for text (common\\text\\quest\\...)
	// Function called with result and pointer needed
	if (loaderPtr == (void*)0x143be59b8)
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


//
// Custom subspecies path
//

static int next_id = 0;
HOOKFUNC(SpawnMonster, void, void* this_ptr, void* unkn, void* ptr, char flag)
{
	int monster_id = *(int*)((char*)this_ptr + 0x158);
	unsigned int subspecies_override = *(int*)((char*)this_ptr + 0x10c);
	if (subspecies_override == 0xCDCDCDCD) 
		subspecies_override = 0;
	else
		next_id = subspecies_override;

	LOG(WARN) << "Creating Monster : " << monster_id
		 << ":" << subspecies_override << " flags " << (int)flag;
	return originalSpawnMonster(this_ptr, unkn, ptr, flag);
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
	AddHook(QuestCount, 0x148b84970); // 83 39 ff 75 f5 c3
	AddHook(QuestFromIndex, 0x148b85350); // 48 63 ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? 8b 04 81 c3 -  result 1 

	// 48 89 5c 24 08 57 48 83 ec 20 89 d3 48 89 cf 89 d9 31 d2 - result 1 and 4
	AddHook(CheckQuestProgress, 0x148b84810);
	AddHook(CheckQuestUnlocked, 0x148b835f0);

	// first func called in check progress and check unlocked
	AddHook(GetQuestCategory, 0x14ad07590);

	// Find UI function with 48 89 5c 24 20 44 89 44 24 18 89 54 24 10 48 89 4c 24 08 55 56 57 41 54 41 55 41 56 41 57 48 83 ec 20 48 89 cd 31 f6
	// Called after an unlock check in that function
	AddHook(CheckStarAndCategory, 0x147bb2040);
	
	// 40 53 56 41 54 41 57 48 81 ec a8 04 00 00 45 89 cc 4c 89 c3 49 89 d7 48 89 ce 4d 85 c0
	AddHook(LoadFilePath, 0x14d3b45e0);

	
	// Subspecies Hooks

	// 40 56 57 41 57 48 81 ec c0 00 00 00 8b 91 58 01 00 00 4d 89 c7 44 8b 81 68 01 00 00 48 89 ce
	AddHook(SpawnMonster, 0x14b237200);

	// 48 89 5c 24 08 44 89 44 24 18 89 54 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8d 6c 24 d9 48 81 ec c0 00 00 00
	AddHook(ConstructMonster, 0x14be83510);

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
