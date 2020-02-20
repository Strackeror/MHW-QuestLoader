#include <iterator>
#include <filesystem>
#include <map>
#include <locale>
#include <nlohmann/json.hpp>
#include <fstream>

#include "ghidra_export.h"
#include "dll.h"
#include "loader.h"
using namespace loader;

// 48 89 e0 41 55 41 57 48 81 ec 68 01 00 00
#define FilePathCheckOffset	0x15ebec410

// 74 44 45 31 c0 48 8d 93 f8 62 21 00 48 8b 02 48 85 c0 74 23 48 8b 4d 08 48 39 48 08 74 28
#define NativePCCheckOffset 0x15ed87808

std::map<std::string, std::string> nativePCList;
bool outputEveryPath = false;

HOOKFUNC(FilePathCheck, void*, void* _0, const char* path, void* _1)
{
	std::string spath(path);
	LOG(INFO) << "File loaded : " << spath;
	return originalFilePathCheck(_0, path, _1);
}

void InjectForceNativePC()
{
	outputEveryPath = ConfigFile.value<bool>("outputEveryPath", false);

	LOG(INFO) << "Hooking Force NativePC";

	// Setting jz to jmp
	unsigned char buf[] = { 0xEB };
	memcpy((char*)MH::File::NativePCCheck + 0x68, buf, 1);

	if (outputEveryPath)
	{
		AddHook(FilePathCheck, MH::File::FilePathCheck);
	}
}