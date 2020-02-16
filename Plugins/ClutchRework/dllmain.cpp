// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <loader.h>
#include <hooks.h>

#include <set>
#include <map>

using namespace loader;

// 48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 20 48 89 d6 48 89 cf 48 85 d2 0f 84 43 01 00 00 48 8b 49 08
#define	TenderizePartAddress	0x14df814d0

//48 81 c1 f0 c3 01 00 45 31 c0
#define TenderizePartMPAddress  0x15dce4170

// 40 53 48 83 ec 20 48 8b 81 70 76 00 00 0f 57 c0 48 89 cb 0f 2f 40 64 73 59 8b 81 20 ea 01 00
#define TurnClawCheckAddress	0x15dcc6740

#define MonsterAddPartTimerAddress 0x1578993d0

// 84 c0 74 1e 48 8b 8b e0 89 00 00 48 8d 54 24 38 41 b8 01 00 00 00 48 8b 89 30 01 00 00
// Substract 0x18
#define LaunchActionAddress		0x15dce8110


//40 55 57 41 56 48 8d ac 24 50 ff ff ff 48 81 ec b0 01 00 00 48 89 cf 49 89 d6 48 8b 49 08 48 85 c9
// Attack Apply		

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

const char* getLastActionName(void* monster)
{
	static const char* none = "NULL";
	void* actionManager = offsetPtr(monster, 0x61c8);
	unsigned int lastActionGroup = *(unsigned int*)offsetPtr(actionManager, 0xac);
	unsigned int lastAction = *(unsigned int*)offsetPtr(actionManager, 0xb0);
	void* actionGroupArray = *(void**)offsetPtr(actionManager, 0x68 + lastActionGroup * 0x10);
	void* action = *(void**)offsetPtr(actionGroupArray, lastAction * 0x8);
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


// rage status -> monster+0x1bddc
// rage count -> monster+0x1bdfc
//  (+0x10 post rajang ?)

static std::map<void*, int> nextSoftenRageCount;

void forceEnrage(void* monster)
{
	LOG(INFO) << "Enrage enforced";
	float* rageBuildUp = offsetPtr<float>(monster, 0x1bdec + 0x4);
	float* rageBuildUp2 = offsetPtr<float>(monster, 0x1bdec + 0x8);
	float* rageTotal = offsetPtr<float>(monster, 0x1bdec + 0x28);
	LOG(INFO) << *rageBuildUp << " " << *rageTotal;
	*rageBuildUp += *rageTotal;
	*rageBuildUp2 += *rageTotal;
	LOG(INFO) << *rageBuildUp << " " << *rageTotal;
}

HOOKFUNC(AddPartTimer, void*, void* timerMgr, unsigned int index, float timerStart)
{
	float* duration = offsetPtr<float>(timerMgr, 0x4a0);
	*duration = 3000;

	void* monster = offsetPtr<void>(timerMgr, -0x1c3f0);
	float* rageBuildUp = offsetPtr<float>(monster, 0x1bdec + 0x4);
	float* rageTotal = offsetPtr<float>(monster, 0x1bdec + 0x28);
	bool enraged = *offsetPtr<bool>(monster, 0x1bdec);
	bool rageReached = (*rageBuildUp >= *rageTotal);
	int rageCount = *offsetPtr<int>(monster, 0x1be0c);

	LOG(INFO) << "TimerMgr" << timerMgr;
	LOG(INFO) << "Monster " << monster << " Rage status : " << enraged << " " << rageReached << " " << rageCount;

	if (enraged || nextSoftenRageCount[monster] > rageCount)
	{
		LOG(INFO) << "AddPartTimer Denying tenderize timer ";
		return nullptr;
	}
	nextSoftenRageCount[monster] = rageCount + 1;
	forceEnrage(monster);
	LOG(INFO) << "AddPartTimer Allowing tenderize timer";
	return originalAddPartTimer(timerMgr, index, timerStart);
}

HOOKFUNC(LaunchAction, bool, void* monster, int actionId)
{
	bool ret = originalLaunchAction(monster, actionId);
	LOG(INFO) << "Monster " << monster << " Action " << getLastActionName(monster);
	if (wordMatches(getLastActionName(monster), std::set<std::string>{"GRAB_CARRY"}))
		forceEnrage(monster);

	return ret;
}


void onLoad()
{
	LOG(INFO) << "ClutchRework Loading...";
	if (std::string(GameVersion) != "402862") {
		LOG(ERR) << "Wrong version";
		return;
	}

	MH_Initialize();

	AddHook(AddPartTimer, MonsterAddPartTimerAddress);
	AddHook(LaunchAction, LaunchActionAddress);
	//AddHook(LoadDamageVals, 0x14df75040);

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

