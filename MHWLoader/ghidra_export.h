
#pragma once
typedef unsigned char undefined; 
typedef unsigned char undefined1; 
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef unsigned char byte; 
typedef unsigned long long ulonglong;
typedef long long longlong;
typedef unsigned int uint;
typedef unsigned short ushort;

namespace MH {
  namespace Monster {
    static void(*dtor)(undefined8 *) = (void(*)(undefined8 *))0x141ca3a10;
    static void *vptr = (void*)0x14344d718;
    namespace DamageBehavior {
      static undefined(*NextAction)() = (undefined(*)())0x1413966e0;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x141cc4590;
    static undefined(*MotionFromId)() = (undefined(*)())0x141bfeab0;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x141ca1130;
    namespace SoftenTimers {
      static undefined(*WoundPartLocal)() = (undefined(*)())0x140afba90;
    }
    static undefined(*GenerateFilePaths)() = (undefined(*)())0x141cce8f0;
  }
  namespace Quest {
    static undefined(*OptionalCount)() = (undefined(*)())0x141354f80;
    static void *OptionalIdList = (void*)0x14324d980;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x141354f70;
    static undefined(*IsMasterRank)() = (undefined(*)())0x141975440;
    static void *GlobalOptionalQuestList = (void*)0x145010ae8;
    static bool(*CheckComplete)(longlong,uint) = (bool(*)(longlong,uint))0x14134e280;
    static undefined(*StarCategoryCheck)() = (undefined(*)())0x140f2b640;
    static undefined(*CheckProgress)() = (undefined(*)())0x14134e310;
    static undefined(*GetCategory)() = (undefined(*)())0x1419744e0;
    namespace QuestData {
      static void *ResourceVtable = (void*)0x1433e8750;
      static undefined(*ResourceFunc)() = (undefined(*)())0x141a0f280;
      static void *ResourcePtr = (void*)0x145009308;
    }
    namespace QuestNoList {
      static void *ResourceVtable = (void*)0x142f83b20;
      static undefined(*ResourceFunc)() = (undefined(*)())0x140478520;
      static void *ResourcePtr = (void*)0x144cb5e40;
    }
    static undefined(*ErrorCheck)(undefined,undefined,undefined,undefined,undefined4,undefined8,undefined8,undefined2,undefined4) = (undefined(*)(undefined,undefined,undefined,undefined,undefined4,undefined8,undefined8,undefined2,undefined4))0x141144830;
  }
  namespace Weapon {
    namespace UI {
      static undefined(*CalcAwakenedElement)() = (undefined(*)())0x14197cc30;
      static uint(*CalcRawBloat)(uint,uint) = (uint(*)(uint,uint))0x14197cc00;
      static void *RawBloatMultipliers = (void*)0x1433b6740;
      namespace Unkn {
        static undefined(*ConditionalElementalBloat)() = (undefined(*)())0x14191a7b0;
      }
      static undefined(*CalcElementalBloat)() = (undefined(*)())0x14197cc20;
    }
  }
  namespace EmSetter {
    static undefined(*CreateMonster)() = (undefined(*)())0x141a6b4f0;
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x140249b20;
  }
  namespace GameVersion {
    static undefined(*CalcNum)() = (undefined(*)())0x1418d4030;
    static void *StringPtr = (void*)0x143eeb1f0;
  }
  namespace String {
    static undefined8(*Format__)(undefined8,undefined8,undefined8,undefined8,undefined) = (undefined8(*)(undefined8,undefined8,undefined8,undefined8,undefined))0x1404639a0;
    static undefined(*Format)() = (undefined(*)())0x1403050f0;
  }
  namespace Chat {
    static undefined(*BuildShowGameMessage_)() = (undefined(*)())0x1419a1fb0;
    static void *MainPtr = (void*)0x14500ac30;
    static void(*ShowGameMessage)(undefined *,undefined *,float,uint,undefined1) = (void(*)(undefined *,undefined *,float,uint,undefined1))0x141a53400;
    namespace Unkn {
      static undefined(*CallBuild)() = (undefined(*)())0x1411b5e50;
    }
    static undefined(*BuildShowGameMessage)() = (undefined(*)())0x1419a2050;
  }
  namespace Damage {
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x1402c7850;
  }
  namespace File {
    static undefined(*LoadResource)() = (undefined(*)())0x142221550;
  }
  namespace QuestBoard {
    static undefined(*FilterQuestList)() = (undefined(*)())0x14114ce60;
  }
  namespace Player {
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x141b8cde0;
    static void *BasePtr = (void*)0x145011710;
  }
}
