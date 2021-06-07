// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "DInput8.h"
#include <fstream>
#include <vector>
#include "../external/MemoryModule/MemoryModule.h"

void LoadLoader()
{
	const char path[] = "loader.dll";
	std::ifstream dll(path, std::ios::binary);
	std::vector<char> dllRead(std::istreambuf_iterator<char>(dll), {});

	size_t size = dllRead.size();
	char* allocatedMem = (char*)malloc(size);
	if (!allocatedMem)
		return;
	memcpy(allocatedMem, &dllRead[0], size);
	auto target = MemoryLoadLibrary(allocatedMem, size);
	typedef void(*initF)(void*);
	((initF)MemoryGetProcAddress(target, "Initialize"))(target);
}
void Init()
{
	// Load the original dinput8.dll from the system directory
	char DInputDllName[MAX_PATH];
	GetSystemDirectoryA(DInputDllName, MAX_PATH);
	strcat_s(DInputDllName, "\\dinput8.dll");
	DInput8DLL = LoadLibraryA(DInputDllName);
	if (DInput8DLL > (HMODULE)31)
	{
		OriginalFunction = (DirectInput8Create_t)GetProcAddress(DInput8DLL, "DirectInput8Create");
	}
	LoadLoader();
}

BOOL APIENTRY DllMain(HMODULE Module,
	DWORD  ReasonForCall,
	LPVOID Reserved)
{
	switch (ReasonForCall)
	{
	case DLL_PROCESS_ATTACH:
		Init();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

