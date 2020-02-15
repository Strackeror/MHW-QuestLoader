// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <loader.h>
#include <hooks.h>

#include <set>

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

char* getLastActionName(void* monster)
{
	void* actionManager = offsetPtr(monster, 0x61c8);
	unsigned int lastActionGroup = *(unsigned int*)offsetPtr(actionManager, 0xac);
	unsigned int lastAction = *(unsigned int*)offsetPtr(actionManager, 0xb0);
	void* actionGroupArray = *(void**)offsetPtr(actionManager, 0x68 + lastActionGroup * 0x10);
	void* action = *(void**)offsetPtr(actionGroupArray, lastAction * 0x8);
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

static std::set<void*> actionUsed;
HOOKFUNC(TurnClawCheck, bool, void* monster)
{
	static std::set<std::string> keywords = { "TURN_L", "TURN_R", "_EXTEND" };
	std::string action(getLastActionName(monster));
	return wordMatches(action, keywords);
}

// rage status -> monster+0x1bddc
// rage count -> monster+0x1bdfc
//  (+0x10 post rajang ?)

static bool allowNextTenderize = false;

bool CheckTenderize(void* monster, float dmg)
{
	static std::set<std::string> keywords = { "_EXTEND" };
	std::string actionName = getLastActionName(monster);
	if (wordMatches(actionName, keywords)
		&& actionUsed.find(monster) == actionUsed.end()
		&& (int)dmg != 20) // prevent claw slap tenderizing
	{
		return true;
	}
	return false;
}

HOOKFUNC(TenderizePart, bool, void* obj, void* data, float dmg)
{
	void* monster = *(void**)offsetPtr(obj, 8);
	LOG(INFO) << "TenderizePart " << getLastActionName(monster) << " " << dmg;
	allowNextTenderize = CheckTenderize(monster, dmg);
	if (allowNextTenderize) actionUsed.emplace(monster);
	return originalTenderizePart(obj, data, dmg);
}

HOOKFUNC(TenderizePartMP, void, void* monster, long long* params)
{
	LOG(INFO) << "TenderizePartMP " << getLastActionName(monster);
	allowNextTenderize = CheckTenderize(monster, 100);
	if (allowNextTenderize) actionUsed.emplace(monster);
	originalTenderizePartMP(monster, params);
}

HOOKFUNC(LoadDamageVals, void, void* dmg, void* _2, void* data)
{
	originalLoadDamageVals(dmg, _2, data);
	float* tenderizer = offsetPtr<float>(data, 0x70);
	if (*tenderizer <= 0.1) return;

	void* monster = *offsetPtr<void*>(dmg, 8);
	if (CheckTenderize(monster, *tenderizer)) *tenderizer = 100;
	LOG(INFO) << "Tenderize Value :" << *tenderizer;
}

HOOKFUNC(AddPartTimer, void*, void* timerMgr, unsigned int index, float timerStart)
{
	float* duration = offsetPtr<float>(timerMgr, 0x4a0);
	if (!allowNextTenderize)
	{
		LOG(INFO) << "AddPartTimer Denying tenderize timer";
		return nullptr;
	}
	LOG(INFO) << "AddPArtTimer Allowing tenderize timer";
	*duration = 3000;
	allowNextTenderize = false;
	return originalAddPartTimer(timerMgr, index, timerStart);
}


HOOKFUNC(LaunchAction, bool, void* monster, int actionId)
{
	if (actionUsed.find(monster) != actionUsed.end())
		actionUsed.erase(monster);
	bool ret = originalLaunchAction(monster, actionId);
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

	AddHook(TenderizePart, TenderizePartAddress);
	AddHook(TenderizePartMP, TenderizePartMPAddress);
	AddHook(AddPartTimer, MonsterAddPartTimerAddress);

	AddHook(TurnClawCheck, TurnClawCheckAddress);
	AddHook(LaunchAction, LaunchActionAddress);

	AddHook(LoadDamageVals, 0x14df75040);

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

