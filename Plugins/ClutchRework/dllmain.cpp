// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <loader.h>
#include <hooks.h>
#include "ghidra_export.h"

#include <set>
#include <map>

using namespace loader;

template<typename T>
inline T* offsetPtr(void* ptr, int offset) { return (T*)(((char*)ptr) + offset); }

static void* offsetPtr(void* ptr, int offset) { return offsetPtr<void>(ptr, offset); }

void DumpMonsterActions(void* monster)
{
	void* actionManager = offsetPtr(monster, 0x61c8);
	void* actionListPtr = offsetPtr(actionManager, 0x68);
	int group = 0;
	int sz = *offsetPtr<int>(actionListPtr, 0x8);
	while (sz > 0)
	{
		LOG(INFO) << group << " " << sz;
		void** actionList = *(void***)actionListPtr;
		for (long long i = 1; i < sz; ++i)
		{
			void* action = actionList[i];
			if (action == nullptr) continue;
			char* actionName = *offsetPtr<char*>(action, 0x20);
			LOG(INFO) << "Group:" << group << " ID:" << i << " Name:" << actionName;
		}
		group++;
		actionListPtr = offsetPtr(actionListPtr, 0x10);
		sz = *offsetPtr<int>(actionListPtr, 0x8);
	}
}


const char*getActionName(void* monster, int actionId, int actionGroup = 1)
{
	static const char* none = "NULL";
	void* actionManager = offsetPtr(monster, 0x61c8);
	void* actionGroupArray = *(void**)offsetPtr(actionManager, 0x68 + actionGroup * 0x10);
	void* action = *(void**)offsetPtr(actionGroupArray, actionId * 0x8);
	if (action == nullptr) return none;
	char* actionName = *(char**)offsetPtr(action, 0x20);

	return actionName;
}

bool wordMatches(std::string actionName, const std::set<std::string>& words)
{
	for (auto find : words)
		if (actionName.find(find) != -1)
			return true;
	return false;
}

void showMessage(std::string message) {
	MH::Chat::ShowGameMessage(*(undefined**)MH::Chat::MainPtr, &message[0], -1, -1, 0);
}


// rage status -> monster+0x1bdec
// rage count -> monster+0x1be0c


void forceEnrage(void* monster)
{
	float* rageBuildUp = offsetPtr<float>(monster, 0x1bdec + 0x4);
	if (*rageBuildUp == 0)
		return;
	LOG(INFO) << "Enrage enforced";
	showMessage("Monster enraged.");
	float* rageBuildUp2 = offsetPtr<float>(monster, 0x1bdec + 0x8);
	float* rageTotal = offsetPtr<float>(monster, 0x1bdec + 0x28);
	LOG(INFO) << *rageBuildUp << " " << *rageTotal;
	*rageBuildUp += *rageTotal;
	*rageBuildUp2 += *rageTotal;
	LOG(INFO) << *rageBuildUp << " " << *rageTotal;
}

struct monsterData {
	int nextSoften;
};

static std::map<void*, monsterData> data;

HOOKFUNC(TurnClawCheck, bool, void* monster)
{
	int rageCount = *offsetPtr<int>(monster, 0x1be0c);
	return originalTurnClawCheck(monster) && (data[monster].nextSoften <= rageCount);
}

HOOKFUNC(AddPartTimer, void*, void* timerMgr, unsigned int index, float timerStart)
{
	void* monster = offsetPtr<void>(timerMgr, -0x1c3f0);
	bool enraged = *offsetPtr<bool>(monster, 0x1bdec);
	int rageCount = *offsetPtr<int>(monster, 0x1be0c);

	if (enraged || data[monster].nextSoften > rageCount)
	{
		LOG(INFO) << "AddPartTimer Denying tenderize timer ";
		return nullptr;
	}
	data[monster].nextSoften = rageCount + 1;
	forceEnrage(monster);
	auto ret = originalAddPartTimer(timerMgr, index, timerStart);
	*offsetPtr<float>(ret, 0xc) = 300;
	LOG(INFO) << "AddPartTimer Allowing tenderize timer " << 300;
	return ret;
}

HOOKFUNC(LaunchAction, bool, void* monster, int actionId)
{
	std::string actionName(getActionName(monster, actionId));
	if (actionName.find("GRAB") != -1 && actionName.find("HIT") != -1) {
		int rageCount = *offsetPtr<int>(monster, 0x1be0c);
		data[monster].nextSoften = rageCount + 1;
		forceEnrage(monster);
	}
	bool ret = originalLaunchAction(monster, actionId);
	LOG(DEBUG) << "Monster " << monster << " Action " << getActionName(monster, actionId);
	return ret;
}


void onLoad()
{
	LOG(INFO) << "ClutchRework Loading...";
	LOG(INFO) << GameVersion;
	if (std::string(GameVersion) != "404549") {
		LOG(ERR) << "Wrong version";
		return;
	}

	MH_Initialize();

	AddHook(AddPartTimer, MH::Monster_AddPartTimer);
	AddHook(LaunchAction, MH::Monster_LaunchAction);
	AddHook(TurnClawCheck, MH::Monster_CanClawTurn);

	MH_ApplyQueued();

	LOG(INFO) << "DONE !";
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        onLoad();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

