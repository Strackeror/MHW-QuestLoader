#include "dll.h"
#include "log.h"


// 40 56 57 41 57 48 81 ec c0 00 00 00 8b 91 68 01 00 00
#define SpawnMonsterOffset		0x156cd95e0

// 44 89 44 24 18 89 54 24 10 48 89 4c 24 08 55 53 56 57 41 54 41 55 41 56 41 57 48 8d 6c 24 e1 48 81 ec a8 00 00 00 48 89 cb
#define ConstructMonsterOffset	0x1576dfe10 

//
// Custom subspecies path
//

static int next_id = 0;
HOOKFUNC(SpawnMonster, void, void* this_ptr, void* unkn, void* ptr, char flag)
{
	int monster_id = *(int*)((char*)this_ptr + 0x168);
	unsigned int subspecies_override = *(int*)((char*)this_ptr + 0x11c);
	if (subspecies_override == 0xCDCDCDCD) 
		subspecies_override = 0;
	else
		next_id = subspecies_override;

	LOG(INFO) << "Creating Monster : " << monster_id << "-" << subspecies_override;
	return originalSpawnMonster(this_ptr, unkn, ptr, flag);
}

HOOKFUNC(ConstructMonster, void*, void* this_ptr, unsigned int monster_id, unsigned int variant)
{
	if (next_id) {
		LOG(WARN) << "Setting Subspecies :" << next_id;
		variant = next_id;
		next_id = 0;
	}
	LOG(INFO) << "Monster constructed : " << monster_id << "-" << variant;
	return originalConstructMonster(this_ptr, monster_id, variant);
}

void InjectSubspeciesLoader()
{
	AddHook(SpawnMonster, SpawnMonsterOffset);
	AddHook(ConstructMonster, ConstructMonsterOffset);
}
