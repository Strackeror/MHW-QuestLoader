#pragma once

#include <windows.h>
#include "MinHook.h"

#define HOOKFUNC(NAME, RET, ...) typedef RET (__fastcall*  t ## NAME)( __VA_ARGS__); \
t##NAME original##NAME; \
RET __fastcall NAME(__VA_ARGS__)

#define AddHook(NAME, OFFSET) do {MH_CreateHook((void*)OFFSET, & NAME, (LPVOID *)& original##NAME); MH_EnableHook((void *)OFFSET);} while(0)

void KillCRCThreads();
void InjectCRCBypass();

void InjectForceNativePC();

void InjectSubspeciesLoader();

void InjectQuestLoader();

