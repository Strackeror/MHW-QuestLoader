// dllmain.cpp : Defines the entry point for the DLL application.

#include "loader.h"
#include "signatures.h"
#include "util.h"
#include <optional>

using namespace loader;
using namespace plugin;

std::string_view plugin::module_name = "MonsterLoader";

void InjectSubspeciesLoader() {
  auto create_monster = find_func(create_monster_sig);
  auto file_paths = find_func(generate_file_paths_sig);

  if (!create_monster || !file_paths) {
    return;
  }

  MH_Initialize();

  static int next_id = 0;
  Hook<void(void *, void *, void *, char)>::hook(*create_monster,
                                                 [](auto original, auto this_ptr, auto unkn, auto ptr, auto flag) {
    int monster_id = *(int *)((char *)this_ptr + 0x168);
    unsigned int subspecies_override = *(int *)((char *)this_ptr + 0x11c);
    if (subspecies_override == 0xCDCDCDCD)
      subspecies_override = 0;
    else
      next_id = subspecies_override;

    return original(this_ptr, unkn, ptr, flag);
  });

  Hook<void *(void *, uint32_t, uint32_t)>::hook(*file_paths,
                                                 [](auto original, auto this_ptr, auto monster_id, auto variant) {
    if (next_id) {
      plugin::log(DEBUG, "Setting subspecies : {} : {}", monster_id, next_id);
      variant = next_id;
      next_id = 0;
    }
    plugin::log(DEBUG, "Creating monster {}-{} {:p}", monster_id, variant, this_ptr);
    return original(this_ptr, monster_id, variant);
  });

  MH_ApplyQueued();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call) {
  case DLL_PROCESS_ATTACH:
    InjectSubspeciesLoader();
    break;
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
