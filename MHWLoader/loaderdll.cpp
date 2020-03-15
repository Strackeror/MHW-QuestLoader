// dllmain.cpp : Defines the entry point for the DLL application.
#include <SDKDDKVer.h>
#include <windows.h>
#include <winternl.h>
#include <TlHelp32.h>

#include <filesystem>

#include "MinHook.h"
#include "loader.h"
#include "dll.h"
#include "ghidra_export.h"

using namespace loader;

const char* loader::GameVersion = "406510";
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

void LoadAllPluginDlls()
{
	if (!std::filesystem::exists("nativePC\\plugins"))
		return;
	for (auto& entry : std::filesystem::directory_iterator("nativePC\\plugins"))
	{
		std::string name = entry.path().filename().string();
		if (entry.path().filename().extension().string() != ".dll") continue;
		LOG(INFO) << "Loading plugin " << entry.path();
		auto dll = LoadLibrary(entry.path().string().c_str());
		if (!dll)
			LOG(ERR) << "Failed to load " << entry.path();

	}
}

void Initialize()
{
	try {
		LoadConfig();
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

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{

	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		Initialize();
	}
	return TRUE;
}
