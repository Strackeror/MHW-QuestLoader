#include <filesystem>
#include <fstream>

#include "log.h"
#include "dll.h"

nlohmann::json ConfigFile;

void LoadConfig()
{
	std::ifstream config("dinput-config.json");
	if (config.fail()) return;

	config >> ConfigFile;
	LOG(INFO) << "Found config file";
}
