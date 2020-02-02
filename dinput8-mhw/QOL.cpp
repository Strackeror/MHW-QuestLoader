
#include "dll.h"
#include "log.h"


// 48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 20 48 89 d6 48 89 cf 48 85 d2 0f 84 43 01 00 00 48 8b 49 08
#define	TenderizePartAddress	0x1468dcbd0

// 40 53 48 83 ec 20 48 8b 81 70 76 00 00 0f 57 c0 48 89 cb 0f 2f 40 64 73 59 8b 81 20 ea 01 00
#define TurnClawCheckAddress	0x14eca4b50


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

static std::chrono::time_point timer = std::chrono::system_clock::now();
static float TenderizeTimer(bool reset = false)
{
	std::chrono::duration<float> time = std::chrono::system_clock::now() - timer;
	if (reset) timer = std::chrono::system_clock::now();
	return time.count();
}

HOOKFUNC(TurnClawCheck, bool, void* monster)
{
	std::string action(getLastActionName(monster));
	if (action.find("TURN_L") != -1 || action.find("TURN_R") != -1 || action.find("_EXTEND") != -1)
		return true;
	return false;
}

// rage status -> monster+0x1bddc
// rage count -> monster+0x1bdfc

HOOKFUNC(TenderizePart, bool, void* obj, void* data, float dmg)
{
	void* monster = *(void**) offsetPtr(obj, 8);

	float* duration = (float*) offsetPtr(monster, 0x1c3e0 + 0x4a0);
	*duration = 5;
	
	char* actionName = getLastActionName(monster);

	LOG(INFO) << "Attempting tenderize : " << actionName << " time since last tenderize : " << TenderizeTimer();
	LOG(INFO) << "Tenderize value : " << dmg;
	if (std::string(actionName).find("_EXTEND") != -1 
		&& TenderizeTimer() > 10
		&& (int) dmg != 20) // prevent turn claw tenderizing
	{
		LOG(INFO) << "Tenderize succesful !";
		TenderizeTimer(true);
		*duration = 3000;
		return originalTenderizePart(obj, data, 100);
	}

	return originalTenderizePart(obj, data, dmg);
}

void InjectQOL()
{
	AddHook(TenderizePart, TenderizePartAddress);
	AddHook(TurnClawCheck, TurnClawCheckAddress);
}