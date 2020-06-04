// dllmain.cpp : Defines the entry point for the DLL application.

#include <filesystem>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>

#include <SDKDDKVer.h>
#include <windows.h>
#include <winternl.h>
#include <TlHelp32.h>


#include "MemoryModule.h"
#include "MinHook.h"

#include "loader.h"
#include "dll.h"
#include "ghidra_export.h"

using namespace loader;

const char* loader::GameVersion = "410918";
const char* invalidVersion = "???";

void InitCodeInjections()
{
	if (std::string(loader::GameVersion) == invalidVersion)
		return;

	MH_Initialize();

	InjectForceNativePC();
	InjectSubspeciesLoader();
	InjectQuestLoader();

	MH_ApplyQueued();
}

static void* currentModule;

HCUSTOMMODULE CustomLoadLibrary(const char* path, void* _) {
	if (std::string(path) == "loader.dll") {
		return currentModule;
	}
	return LoadLibraryA(path);
}

FARPROC CustomGetProcAddress(HCUSTOMMODULE target, const char* path, void* _) {
	if (target == currentModule) {
		return MemoryGetProcAddress(target, path);
	}
	return GetProcAddress((HMODULE)target, path);
}

auto LoadDll(const char* path)
{
	std::ifstream dll(path, std::ios::binary);
	std::vector<char> dllRead(std::istreambuf_iterator<char>(dll), {});

	size_t size = dllRead.size();
	char* allocatedMem = (char*)malloc(size);
	memcpy(allocatedMem, &dllRead[0], size);
	
	return MemoryLoadLibraryEx(allocatedMem, size, MemoryDefaultAlloc, MemoryDefaultFree, 
		CustomLoadLibrary, CustomGetProcAddress, MemoryDefaultFreeLibrary, 
		nullptr);
}

void LoadAllPluginDlls()
{
	if (!ConfigFile.value("enablePluginLoader", true)) return;
	if (!std::filesystem::exists("nativePC\\plugins"))
		return;
	for (auto& entry : std::filesystem::directory_iterator("nativePC\\plugins"))
	{
		std::string name = entry.path().filename().string();
		if (entry.path().filename().extension().string() != ".dll") continue;
		LOG(INFO) << "Loading plugin " << entry.path();
		auto dll = LoadDll(entry.path().string().c_str());
		if (!dll)
			LOG(ERR) << "Failed to load " << entry.path();

	}
}

void OldWarning() {
	if (std::filesystem::exists("hid.dll")) {
		LOG(ERR) << "Found old hid.dll in game folder.";
		LOG(ERR) << "This dll is not used by the mod anymore, and might cause issues.";
		LOG(ERR) << "Please delete hid.dll from the game's folder.";
	}
}

extern "C" {
	__declspec(dllexport) extern void Initialize(void* memModule)
	{
		currentModule = memModule;
		try {
			LoadConfig();
			OldWarning();
			if (memcmp((const char*)MH::GameVersion::String, loader::GameVersion, 6) != 0)
			{
				GameVersion = invalidVersion;
				LOG(ERR) << "Build Number check failed.";
				LOG(ERR) << "Wrong Version of MHW detected";
				LOG(ERR) << "Loader needs to be updated.";
			}
			LoadAllPluginDlls();
			InitCodeInjections();
		}
		catch (std::exception e)
		{
			MessageBox(0, "STRACKER'S LOADER ERROR", e.what(), MB_OK);
		}
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}
