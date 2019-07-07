// dllmain.cpp : Defines the entry point for the DLL application.
#include <SDKDDKVer.h>
#include <windows.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include "MinHook.h"

typedef HRESULT(WINAPI* tDirectInput8Create)(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk);
tDirectInput8Create oDirectInput8Create = nullptr;


class Quest {
public:
	static std::vector<Quest> Quests;
	static void PopulateQuests() 
	{
		for (auto& entry : std::filesystem::directory_iterator("nativePC/quest"))
		{
			std::string name = entry.path().filename().string();
			if (entry.path().filename().extension().string() != ".mib") continue;

			int id;
			if (sscanf_s(name.c_str(), "questData_%d.mib", &id) != 1) continue;
			if (id < 90000) continue;

			std::cout << "found quest: " << id << std::endl;
			Quests.push_back(Quest(id));
		}
	}

	int file_id;
	int starcount = 10;

	Quest(int id) : file_id(id) { }
};

std::vector<Quest> Quest::Quests;

typedef bool(__fastcall* tCheckIfQuestIsUnlocked)(void* this_ptr, unsigned int id);

tCheckIfQuestIsUnlocked originalQuestUnlocked;
bool __fastcall QuestUnlocked(void* this_ptr, unsigned int id)
{
	for (auto quest : Quest::Quests)
	{
		if (quest.file_id == id) {
			//std::cout << "QuestUnlocked" << id << std::endl;
			return true;
		}
	}
	return originalQuestUnlocked(this_ptr, id);
}


typedef int(__fastcall* tGetQuestCount)();
tGetQuestCount originalQuestCount;

int __fastcall GetQuestCount()
{
	//std::cout << "QuestCount" << std::endl;
	return originalQuestCount() + Quest::Quests.size();
}


typedef int(__fastcall* tGetQuestFromIndex)(void* this_ptr, int index);
tGetQuestFromIndex originalQuestFromIndex;

int __fastcall GetQuestFromIndex(void* this_ptr, int index)
{
	if (index >= originalQuestCount())
	{
		//std::cout << "QuestFromIndex" << index << ":" << Quest::Quests[index - originalQuestCount()].file_id << std::endl;
		return Quest::Quests[index - originalQuestCount()].file_id;
	}
	return originalQuestFromIndex(this_ptr, index);
}

typedef bool(__fastcall* tCheckStarAndCategory)(int questID, int category, int starCount);
tCheckStarAndCategory originalCheckStarAndCategory;

bool __fastcall CheckStarAndCategory(int questID, int category, int starCount)
{
	for (auto quest : Quest::Quests)
	{
		if (questID != quest.file_id) continue;
		//std::cout << "CheckStarAndCategory" << questID << std::endl;
		if (category == 1 && starCount == quest.starcount) return true;
		return false;
	}
	return originalCheckStarAndCategory(questID, category, starCount);
}

typedef int(__fastcall* tGetQuestCategory)(int questID, int unkn);
tGetQuestCategory originalGetQuestCategory;

int __fastcall GetQuestCategory(int questID, int unkn)
{
	for (auto quest : Quest::Quests)
	{
		if (questID == quest.file_id) {
			//std::cout << "QuestCategory" << questID << std::endl;
			return 1;
		}
	}
	return originalGetQuestCategory(questID, unkn);
}


void Initialize()
{
	char syspath[MAX_PATH];
	GetSystemDirectory(syspath, MAX_PATH);
	strcat_s(syspath, "\\dinput8.dll");
	HMODULE hMod = LoadLibrary(syspath);
	oDirectInput8Create = (tDirectInput8Create)GetProcAddress(hMod, "DirectInput8Create");

	Quest::PopulateQuests();

	std::cout << "Hooking\n";
	MH_Initialize();
	MH_CreateHook((void*)0x14862cda0, &QuestUnlocked, (LPVOID *) &originalQuestUnlocked);
	MH_EnableHook((void*)0x14862cda0);

	MH_CreateHook((void*)0x14862d1e0, &GetQuestCount, (LPVOID*)& originalQuestCount);
	MH_EnableHook((void*)0x14862d1e0);

	MH_CreateHook((void*)0x14862d220, &GetQuestFromIndex, (LPVOID*)& originalQuestFromIndex);
	MH_EnableHook((void*)0x14862d220);
	
	MH_CreateHook((void*)0x14a8d87a0, &GetQuestCategory, (LPVOID*)& originalGetQuestCategory);
	MH_EnableHook((void*)0x14a8d87a0);
	
	MH_CreateHook((void*)0x147735140, &CheckStarAndCategory, (LPVOID*)& originalCheckStarAndCategory);
	MH_EnableHook((void*)0x147735140);

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		AllocConsole();
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		DisableThreadLibraryCalls(hModule);
		Initialize();
	}
	return TRUE;
}

HRESULT WINAPI DirectInput8Create(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk)
{
	return oDirectInput8Create(inst_handle, version, r_iid, out_wrapper, p_unk);
}
