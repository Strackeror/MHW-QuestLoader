#pragma once

#include <windows.h>
#include <nlohmann/json.hpp>
#include "util.h"

extern nlohmann::json ConfigFile;
void LoadConfig();
