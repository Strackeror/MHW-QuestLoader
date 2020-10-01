
#pragma once
typedef unsigned char undefined; 
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef unsigned char byte; 
typedef unsigned long long ulonglong;
typedef long long longlong;
typedef unsigned int uint;
typedef unsigned short ushort;

namespace MH {
  namespace Quest {
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x141359970;
    static void *OptionalIdList = (void*)0x14329f6b0;
    static bool(*StarCategoryCheck)(undefined8,ulonglong,undefined4,undefined8) = (bool(*)(undefined8,ulonglong,undefined4,undefined8))0x146d8bfe0;
    static undefined8(*GetCategory)(undefined8) = (undefined8(*)(undefined8))0x147bd96b0;
    static bool(*IsMasterRank)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x147be1b40;
    static undefined8(*ErrorCheck)(undefined,undefined,undefined,undefined,undefined4,undefined8,undefined8,undefined2,undefined4) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined4,undefined8,undefined8,undefined2,undefined4))0x1411425a0;
    static bool(*CheckComplete)(longlong,uint) = (bool(*)(longlong,uint))0x141352940;
    static bool(*CheckProgress)(longlong,uint) = (bool(*)(longlong,uint))0x1413529c0;
    static undefined8(*OptionalCount)() = (undefined8(*)())0x141359980;
    static void *GlobalOptionalQuestList = (void*)0x145069fa8;
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144d0ea98;
    }
    namespace QuestData {
      static void *ResourcePtr = (void*)0x145062838;
    }
  }
  namespace Monster {
    namespace SoftenTimers {
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140af2450;
    }
    static undefined8 *(*ctor)(undefined8 *,undefined4,undefined4) = (undefined8 *(*)(undefined8 *,undefined4,undefined4))0x141cb4a90;
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x141cd7e40;
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x14139b0e0;
    }
  }
  namespace Player {
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x141ba0f00;
    static void *BasePtr = (void*)0x14506ab60;
  }
  namespace Damage {
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x1402c78f0;
  }
  namespace QuestBoard {
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x14114b9a0;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x141360430;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x1418dbec0;
    static void *StringPtr = (void*)0x143f43f70;
    static void *String = (void*)0x14329c878;
  }
  namespace String {
    static undefined8(*Format__)(undefined8,undefined8,undefined8,undefined8,undefined) = (undefined8(*)(undefined8,undefined8,undefined8,undefined8,undefined))0x140461410;
  }
  namespace File {
    static undefined8(*LoadResource)() = (undefined8(*)())0x142238460;
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x141a74fd0;
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x1402492e0;
  }
}
