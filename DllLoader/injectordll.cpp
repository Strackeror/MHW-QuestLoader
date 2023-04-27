
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <string>

#include <windows.h>
#include <stdio.h>

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
		LoadLoader();
	}
	return (FALSE);
}

