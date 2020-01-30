
#include "dll.h"
#include "log.h"

void* offsetPtr(void* ptr, int offset) { return ((char*)ptr) + offset; }


HOOKFUNC(TenderizePart, bool, void* obj, void* data, float a)
{
	void* monster = *(void**) offsetPtr(obj, 8);
	float* duration = (float*) offsetPtr(monster, 0x1c3e0 + 0x4a0);
	
	void* actionManager = offsetPtr(monster, 0x61c8);

	unsigned int lastActionGroup = *(unsigned int*)offsetPtr(actionManager, 0xac);
	unsigned int lastAction = *(unsigned int*)offsetPtr(actionManager, 0xb0);

	LOG(INFO) << lastAction;

	void* actionGroupArray = *(void**)offsetPtr(actionManager, 0x68 + lastActionGroup * 0x10);
	LOG(INFO) << actionGroupArray;
	void* action = *(void**)offsetPtr(actionGroupArray, lastAction * 0x8);
	LOG(INFO) << action;
	char* actionName = *(char**)offsetPtr(action, 0x20);

	

	LOG(INFO) << "Part tenderized";
	LOG(INFO) << "tenderize progress : " << a;
	LOG(INFO) << "duration : " << *duration;
	LOG(INFO) << lastAction << ":" << actionName;

	return originalTenderizePart(obj, data, a);
}

void InjectQOL()
{
	AddHook(TenderizePart, 0x1468dcbd0);
}