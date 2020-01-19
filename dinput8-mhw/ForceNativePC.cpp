#include "dll.h"
#include "log.h"

#include <iterator>
#include <filesystem>
#include <map>
#include <locale>

// 48 89 e0 41 55 41 57 48 81 ec 68 01 00 00
#define FilePathCheckOffset	0x1609bc430

std::map<std::string, std::string> nativePCList;

HOOKFUNC(FilePathCheck, void*, void* _0, const char* path, void* _1)
{
	std::string spath(path);
	if (nativePCList.find(spath) == nativePCList.end())
		return originalFilePathCheck(_0, path, _1);
	LOG(INFO) << "File loaded : " << spath;
	return originalFilePathCheck(_0, nativePCList[spath].c_str(), _1);
}

void FetchNativePCFiles()
{
	for (auto entry : std::filesystem::recursive_directory_iterator("nativePC"))
	{
		if (!entry.is_regular_file()) continue;
		std::string path = entry.path().string();
		path.erase(0, 9);
		nativePCList["native:\\" + path] = "nativePC:\\" + path;
	}
}

void InjectForceNativePC()
{
	FetchNativePCFiles();
	if (!nativePCList.empty())
	{
		LOG(INFO) << "Hooking Force NativePC";
		AddHook(FilePathCheck, FilePathCheckOffset);
	}
}