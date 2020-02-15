#pragma once
#include "MinHook.h"

#define HOOKFUNC(NAME, RET, ...) typedef RET (__fastcall*  t ## NAME)( __VA_ARGS__); \
t##NAME original##NAME; \
RET __fastcall NAME(__VA_ARGS__)

#define AddHook(NAME, OFFSET) do {MH_CreateHook((void*)OFFSET, & NAME, (LPVOID *)& original##NAME); MH_QueueEnableHook((void *)OFFSET);} while(0)