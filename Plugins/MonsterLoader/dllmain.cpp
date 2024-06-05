// dllmain.cpp : Defines the entry point for the DLL application.

#include <optional>

#include "loader.h"
#include "scanmem.h"
#include "util.h"

using namespace loader;

const char* CREATE_MONSTER_BITS =
    "01000... 01010... 01010... 01000... 01010... 01001... 10000001 11101... "
    "........ ........ ........ ........ 10001011 10...... ........ ........ "
    "........ ........ 01001... 10001011 11...... 01000... 10001011 10...... "
    "........ ........ ........ ........ 01001... 10001011 11...... 01001... "
    "10001011 00...101 ........ ........ ........ ........ 01000... 10110... "
    "........ 11101000 ........ ........ ........ ........ 01001... 10001001 "
    "10...... ........ ........ ........ ........ 01001... 10001011 11...... "
    "01001... 10000101 11...... 00001111 10000100 ........ ........ ........ "
    "........";

const char* GENERATE_FILE_PATHS_BITS =
    "01001... 10001001 01...100 ..100... ........ 01001... 10001001 01...100 "
    "..100... ........ 01001... 10001001 01...100 ..100... ........ 01001... "
    "10001001 01...100 ..100... ........ 01000... 01010... 01000... 01010... "
    "01000... 01010... 01001... 10000011 11101... ........ 01001... 10001011 "
    "11...... 01000... 10001011 11...... 10001011 11...... 11101000 ........ "
    "........ ........ ........ 01001... 10001101 10...... ........ ........ "
    "........ ........ 01001... 10001101 00...101 ........ ........ ........ "
    "........ 01001... 10001011 11...... 01001... 10001011 01...... ........ "
    "11101000 ........ ........ ........ ........ 01001... 10001011 11...... "
    "11101000 ........ ........ ........ ........";

std::optional<byte*> find_func(std::string_view binary) {
  auto [bytes, mask] = parseBinary(binary);
  auto found = scanmem(bytes, mask);
  if (found.size() != 1) {
    return {};
  }
  return found[0];
}

void InjectSubspeciesLoader() {
  auto create_monster = find_func(CREATE_MONSTER_BITS);
  if (!create_monster) {
    LOG(loader::ERR) << "Failed to find function create monster";
    return;
  }

  auto file_paths = find_func(GENERATE_FILE_PATHS_BITS);
  if (!file_paths) {
    LOG(loader::ERR) << "failed to find function for file paths";
  }

  MH_Initialize();

  static int next_id = 0;
  Hook<void(void*, void*, void*, char)>::hook(
      *create_monster,
      [](auto original, auto this_ptr, auto unkn, auto ptr, auto flag) {
        int monster_id = *(int*)((char*)this_ptr + 0x168);
        unsigned int subspecies_override = *(int*)((char*)this_ptr + 0x11c);
        if (subspecies_override == 0xCDCDCDCD)
          subspecies_override = 0;
        else
          next_id = subspecies_override;

        return original(this_ptr, unkn, ptr, flag);
      });

  Hook<void*(void*, uint32_t, uint32_t)>::hook(
      *file_paths,
      [](auto original, auto this_ptr, auto monster_id, auto variant) {
        if (next_id) {
          LOG(INFO) << "Setting Subspecies : " << monster_id << ":" << next_id;
          variant = next_id;
          next_id = 0;
        }
        LOG(INFO) << "Creating Monster : " << monster_id << "-" << variant
                  << " @0x" << this_ptr;
        return original(this_ptr, monster_id, variant);
      });

  MH_ApplyQueued();
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
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
