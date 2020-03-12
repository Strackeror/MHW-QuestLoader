#include <filesystem>
#include <fstream>

#include "loader.h"
#include "dll.h"

using namespace loader;

nlohmann::json ConfigFile = nlohmann::json::object();

void LoadConfig()
{
	ConfigFile = nlohmann::json::object();
	std::ifstream config("loader-config.json");
	if (config.fail()) return;

	config >> ConfigFile;
	LOG(INFO) << "Found config file";
}
