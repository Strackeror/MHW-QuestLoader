#include <windows.h>
#include "DInput8.h"

void LoadLoader() 
{
	const char path[] = "./loader.dll";
	auto module = LoadLibraryA(path);
	if (!module) {
		MessageBoxA(nullptr, "Stracker's loader error", "loader.dll not found", 1);
		return;
	}
	auto initialize = GetProcAddress(module, "Initialize");
	initialize();

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

