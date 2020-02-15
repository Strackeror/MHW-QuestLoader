// dllmain.cpp : Defines the entry point for the DLL application.
#include <SDKDDKVer.h>
#include <windows.h>
#include <winternl.h>
#include <TlHelp32.h>

#include <filesystem>

#include "MinHook.h"
#include "loader.h"
#include "dll.h"

using namespace loader;

// search for build number as string
#define BuildNumberOffset	0x14307c298
const char* loader::GameVersion = "402862";


void InitCodeInjections()
{

	if (strcmp((const char*)BuildNumberOffset, GameVersion) != 0)
	{
		LOG(ERR) << "Build Number check failed.";
		LOG(ERR) << "Wrong Version of MHW detected";
		LOG(ERR) << "Loader needs to be updated.";
		return;
	}

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

typedef HRESULT(WINAPI* tDirectInput8Create)(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk);
tDirectInput8Create oDirectInput8Create = nullptr;

void Initialize()
{
	char syspath[MAX_PATH];
	GetSystemDirectory(syspath, MAX_PATH);
	strcat_s(syspath, "\\dinput8.dll");
	HMODULE hMod = LoadLibrary(syspath);
	oDirectInput8Create = (tDirectInput8Create)GetProcAddress(hMod, "DirectInput8Create");

	LoadConfig();
	LoadAllPluginDlls(); 
	InitCodeInjections();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{

	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		Initialize();
	}
	return TRUE;
}

HRESULT WINAPI DirectInput8Create(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk)
{
	return oDirectInput8Create(inst_handle, version, r_iid, out_wrapper, p_unk);
}
