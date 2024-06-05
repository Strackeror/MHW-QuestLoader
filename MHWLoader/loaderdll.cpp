#include <filesystem>
#include <vector>

#include <SDKDDKVer.h>
#include <windows.h>
#include <winternl.h>
#include <TlHelp32.h>


#include "loader.h"
#include "dll.h"
#include "ghidra_export.h"
#include "memory_patch.h"

using namespace loader;

const char* loader::GameVersion = "???";

static void* currentModule;

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
		auto dll = LoadLibraryA(entry.path().string().c_str());
		if (!dll)
			LOG(ERR) << "Failed to load " << entry.path();

	}
}

void OldWarning() {
	if (std::filesystem::exists("dtdata.dll") || std::filesystem::exists("hid.dll")) {
		LOG(ERR) << "Found old dlls in game folder.";
		LOG(ERR) << "Please delete hid.dll and/or dtdata.dll from the game folder if they exist.";
		LOG(ERR) << "They are obsolete files from previous versions of this mod.";
	}
}

static std::string GameVersionString;


void FindVersion() {
  const auto CalcNumBits =
      "01001... 10001101 01001100 ..100100 00110000 01001... 10001101 01000010 "
      "11110101";
  auto [binData, binMask] = parseBinary(CalcNumBits);
  auto found = scanmem(binData, binMask);
  if (found.size() != 1) {
    LOG(ERR) << "Build Number check failed.";
    LOG(ERR) << "Could not find game version";
    LOG(ERR) << "Loader needs to be updated.";
    return;
  }

  byte* instruction = found[0] - 0x18;
  char** exeGameVersion =
    (char**)(instruction + *(uint32_t*)(instruction + 0x3) + 0x7);
  GameVersionString = *exeGameVersion;
  GameVersion = GameVersionString.c_str();
}


extern "C" {
	__declspec(dllexport) extern void Initialize()
	{
		try {
			LoadConfig();
			OldWarning();
			FindVersion();
			LoadAllPluginDlls();
			return;
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
