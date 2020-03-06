#pragma once

#include "MinHook.h"

template<typename T>
inline T* offsetPtr(void* ptr, int offset) { return (T*)(((char*)ptr) + offset); }

#define SHOW(VAR) "\""#VAR"\"={" << VAR << "}"

#define DeclareHook(TARGET, NAME, RET, PARAMS) \
namespace hooks::NAME {\
	static void* target = TARGET;\
	RET hook PARAMS; \
	static RET(*original) PARAMS;\
}\
RET hooks::NAME::hook PARAMS

#define CreateHook(ADDR, NAME, RET, ...) DeclareHook(ADDR, NAME, RET, (__VA_ARGS__))


#define QueueHook(NAME) \
 do {\
	MH_CreateHook(hooks::NAME::target, &hooks::NAME::hook, (LPVOID *)&hooks::NAME::original);\
	MH_QueueEnableHook(hooks::NAME::target);\
} while(0) 


template<typename R, typename ...Args>
void CreateHookFunction(R(*target)(Args...), R(*hook)(Args...), R(**trampoline)(Args...)) {
	MH_CreateHook(target, hook, (LPVOID*)trampoline);
}

#define HookLambda(TARGET, LAMBDA) do {\
	static decltype(TARGET) original;\
	CreateHookFunction(TARGET, (decltype(TARGET)) LAMBDA, &original);\
	MH_QueueEnableHook(TARGET);\
} while(false)

