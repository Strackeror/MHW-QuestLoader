#include "dll.h"
#include "log.h"


// 40 56 57 41 57 48 81 ec c0 00 00 00 8b 91 58 01 00 00 4d 89 c7 44 8b 81 68 01 00 00 48 89 ce
#define SpawnMonsterOffset		0x14ea6e960

// 48 89 5c 24 08 44 89 44 24 18 89 54 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8d 6c 24 d9 48 81 ec c0 00 00 00
#define ConstructMonsterOffset	0x14f30d4a0 

//
// Custom subspecies path
//

static int next_id = 0;
HOOKFUNC(SpawnMonster, void, void* this_ptr, void* unkn, void* ptr, char flag)
{
	int monster_id = *(int*)((char*)this_ptr + 0x168);
	unsigned int subspecies_override = *(int*)((char*)this_ptr + 0x10c);
	if (subspecies_override == 0xCDCDCDCD) 
		subspecies_override = 0;
	else
		next_id = subspecies_override;

	LOG(WARN) << "Creating Monster : " << monster_id
		 << ":" << subspecies_override << " flags " << (int)flag;
	return originalSpawnMonster(this_ptr, unkn, ptr, flag);
}

HOOKFUNC(ConstructMonster, void*, void* this_ptr, unsigned int monster_id, unsigned int variant)
{
	if (next_id) {
		LOG(WARN) << "Setting Subspecies :" << next_id;
		variant = next_id;
		next_id = 0;
	}
	return originalConstructMonster(this_ptr, monster_id, variant);
}

void InjectSubspeciesLoader()
{
	AddHook(SpawnMonster, SpawnMonsterOffset);
	AddHook(ConstructMonster, ConstructMonsterOffset);
}
