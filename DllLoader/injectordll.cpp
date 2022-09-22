
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <string>

#include <windows.h>
#include <stdio.h>
#include "DInput8.h"
#include "../external/MemoryModule/MemoryModule.h"

void LoadLoader() 
{
	const char path[] = "loader.dll";
	std::ifstream dll(path, std::ios::binary);
	std::vector<char> dllRead(std::istreambuf_iterator<char>(dll), {});

	size_t size = dllRead.size();
	char* allocatedMem = (char*) malloc(size);
	if (!allocatedMem)
		return;
	memcpy(allocatedMem, &dllRead[0], size);
	auto target = MemoryLoadLibrary(allocatedMem, size);
	typedef void(*initF)(void*);
	((initF)MemoryGetProcAddress(target, "Initialize"))(target);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		char path[MAX_PATH];
		GetSystemDirectoryA(path, MAX_PATH);
		strcat_s(path, "\\dinput8.dll");
		hMod = LoadLibrary(path);
		if (hMod > (HMODULE)31) {
			oDirectInput8Create = (tDirectInput8Create)GetProcAddress(hMod, "DirectInput8Create");
		}

		LoadLoader();
	}
	return (TRUE);
}

