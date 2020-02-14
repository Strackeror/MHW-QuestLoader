#pragma once

#include <windows.h>
#include <nlohmann/json.hpp>
#include "hooks.h"



extern nlohmann::json ConfigFile;
void LoadConfig();

void InjectForceNativePC();

void InjectSubspeciesLoader();

void InjectQuestLoader();

void InjectQOL();
