#include <filesystem>
#include <fstream>

#include "loader.h"
#include "dll.h"

using namespace loader;

nlohmann::json ConfigFile;

void LoadConfig()
{
	ConfigFile = nlohmann::json::object();
	std::ifstream config("dinput-config.json");
	if (config.fail()) return;

	config >> ConfigFile;
	LOG(INFO) << "Found config file";
}
