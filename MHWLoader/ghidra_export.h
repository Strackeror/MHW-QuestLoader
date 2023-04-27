
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
  namespace Quest {
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x14114e510;
    static undefined8(*CheckProgress)() = (undefined8(*)())0x14135e260;
    static undefined8(*GetCategory)(undefined8) = (undefined8(*)(undefined8))0x1419875c0;
    static void *OptionalIdList = (void*)0x1432a7cb0;
    static bool(*CheckComplete)(longlong,uint) = (bool(*)(longlong,uint))0x14135e1e0;
    static undefined8(*OptionalCount)() = (undefined8(*)())0x141365290;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x141365280;
		static bool(*IsMasterRank)(undefined8, undefined8, undefined8, undefined8) = (bool(*)(undefined8, undefined8, undefined8, undefined8))0x1419885c0;
    static void *GlobalOptionalQuestList = (void*)0x145073258;
    static bool(*StarCategoryCheck)(int,int,int) = (bool(*)(int,int,int))0x140f347b0;
    namespace QuestData {
      static void *ResourceVtable = (void*)0x143442ac0;
      static undefined8(*ResourceFunc)() = (undefined8(*)())0x141a22de0;
      static void *ResourcePtr = (void*)0x14506ba18;
    }
    namespace QuestNoList {
      static void *ResourceVtable = (void*)0x142fdde48;
      static undefined8(*ResourceFunc)() = (undefined8(*)())0x140479500;
      static void *ResourcePtr = (void*)0x144d17e20;
    }
  }
  namespace Player {
    static void *BasePtr = (void*)0x145073e80;
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x141ba9280;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x14136bdf0;
  }
  namespace Monster {
    static void(*dtor)(undefined8 *) = (void(*)(undefined8 *))0x141cbff80;
    static void *vptr = (void*)0x1434a7a20;
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x1413a6bf0;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x141ce0a50;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x141cbd6a0;
    namespace SoftenTimers {
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140aff490;
    }
    static undefined8(*MotionFromId)() = (undefined8(*)())0x141c1afa0;
    static undefined8(*GetEmName)(uint) = (undefined8(*)(uint))0x1413af000;
    static undefined8(*GenerateFilePaths)() = (undefined8(*)())0x141ceadc0;
    static void *EmNameList = (void*)0x143f51c40;
  }
  namespace Weapon {
    namespace UI {
      static undefined8(*CalcAwakenedElement)() = (undefined8(*)())0x1419900b0;
      static uint(*CalcRawBloat)(uint,uint) = (uint(*)(uint,uint))0x141990080;
      static void *RawBloatMultipliers = (void*)0x143410b78;
      namespace Unkn {
        static undefined8(*ConditionalElementalBloat)() = (undefined8(*)())0x14192cc00;
      }
      static undefined8(*CalcElementalBloat)() = (undefined8(*)())0x1419900a0;
    }
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x141a7f4e0;
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x140249d10;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x1418e61d0;
    static void *StringPtr = (void*)0x143f4d1d0;
  }
  namespace String {
    static undefined8(*Format__)(undefined8,undefined8,undefined8,undefined8,undefined) = (undefined8(*)(undefined8,undefined8,undefined8,undefined8,undefined))0x1404649a0;
    static undefined8(*Format)() = (undefined8(*)())0x140306110;
    static undefined8(*sPrintf)() = (undefined8(*)())0x14024c520;
  }
  namespace Chat {
    static undefined8(*BuildShowGameMessage_)() = (undefined8(*)())0x1419b5430;
    static void *MainPtr = (void*)0x14506d340;
    static void(*ShowGameMessage)(undefined *,undefined *,float,uint,undefined1) = (void(*)(undefined *,undefined *,float,uint,undefined1))0x141a671f0;
    namespace Unkn {
      static undefined8(*CallBuild)() = (undefined8(*)())0x1411c0c30;
    }
    static undefined8(*BuildShowGameMessage)() = (undefined8(*)())0x1419b54d0;
  }
  namespace Damage {
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x1402c84d0;
  }
  namespace File {
    static undefined8(*LoadResource)() = (undefined8(*)())0x14223ef10;
  }
  namespace QuestBoard {
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x141157940;
  }
}
