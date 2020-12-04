
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
    static void(*dtor)(undefined8 *) = (void(*)(undefined8 *))0x141cbff30;
    static void *vptr = (void*)0x1434a7a20;
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x1413a6ba0;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x141ce0a00;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x141cbd650;
    namespace SoftenTimers {
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140aff490;
    }
  }
  namespace Quest {
    static undefined8(*OptionalCount)() = (undefined8(*)())0x141365240;
    static void *OptionalIdList = (void*)0x1432a7cb0;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x141365230;
    static bool(*IsMasterRank)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x1602defc0;
    static void *GlobalOptionalQuestList = (void*)0x145073248;
    static bool(*CheckComplete)(longlong,uint) = (bool(*)(longlong,uint))0x14135e190;
    static undefined8(*GetCategory)(undefined8) = (undefined8(*)(undefined8))0x1602d6560;
    static bool(*StarCategoryCheck)(undefined8,ulonglong,undefined4,undefined8) = (bool(*)(undefined8,ulonglong,undefined4,undefined8))0x1463a14f0;
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x14114e4c0;
    static undefined8(*CheckProgress)() = (undefined8(*)())0x14135e210;
    namespace QuestData {
      static void *ResourceVtable = (void*)0x143442ac0;
      static undefined8(*ResourceFunc)() = (undefined8(*)())0x141a22d90;
      static void *ResourcePtr = (void*)0x14506ba08;
    }
    namespace QuestNoList {
      static void *ResourceVtable = (void*)0x142fdde48;
      static undefined8(*ResourceFunc)() = (undefined8(*)())0x140479500;
      static void *ResourcePtr = (void*)0x144d17e20;
    }
  }
  namespace Weapon {
    namespace UI {
      static undefined8(*CalcAwakenedElement)() = (undefined8(*)())0x141990060;
      static uint(*CalcRawBloat)(uint,uint) = (uint(*)(uint,uint))0x141990030;
      static void *RawBloatMultipliers = (void*)0x143410b78;
      namespace Unkn {
        static undefined8(*ConditionalElementalBloat)() = (undefined8(*)())0x14192cbb0;
      }
      static undefined8(*CalcElementalBloat)() = (undefined8(*)())0x141990050;
    }
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x141a7f490;
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x140249d10;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x1418e6180;
    static void *StringPtr = (void*)0x143f4d1d0;
    static void *String = (void*)0x1432a4e70;
  }
  namespace String {
    static undefined8(*Format__)(undefined8,undefined8,undefined8,undefined8,undefined) = (undefined8(*)(undefined8,undefined8,undefined8,undefined8,undefined))0x1404649a0;
    static undefined8(*Format)() = (undefined8(*)())0x140306110;
  }
  namespace Chat {
    static undefined8(*BuildShowGameMessage_)() = (undefined8(*)())0x1419b53e0;
    static void *MainPtr = (void*)0x14506d330;
    static void(*ShowGameMessage)(undefined *,undefined *,float,uint,undefined1) = (void(*)(undefined *,undefined *,float,uint,undefined1))0x141a671a0;
    namespace Unkn {
      static undefined8(*CallBuild)() = (undefined8(*)())0x1411c0be0;
    }
    static undefined8(*BuildShowGameMessage)() = (undefined8(*)())0x1419b5480;
  }
  namespace Damage {
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x1402c84d0;
  }
  namespace File {
    static undefined8(*LoadResource)() = (undefined8(*)())0x14223eec0;
  }
  namespace QuestBoard {
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x1411578f0;
  }
  namespace Player {
    static void *BasePtr = (void*)0x145073e70;
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x141ba9230;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x14136bda0;
  }
}
