
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
    static undefined8(*ErrorCheck)(undefined,undefined,undefined,undefined,undefined4,undefined8,undefined8,undefined2,undefined4) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined4,undefined8,undefined8,undefined2,undefined4))0x141142980;
    static bool(*CheckProgress)(longlong,uint) = (bool(*)(longlong,uint))0x141352da0;
    static undefined8(*GetCategory)(undefined8) = (undefined8(*)(undefined8))0x1631334d0;
    static void *OptionalIdList = (void*)0x14329f6b0;
    static bool(*CheckComplete)(longlong,uint) = (bool(*)(longlong,uint))0x141352d20;
    static undefined8(*OptionalCount)() = (undefined8(*)())0x141359d60;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x141359d50;
    static bool(*IsMasterRank)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x16313bad0;
    static void *GlobalOptionalQuestList = (void*)0x145069fb8;
    static bool(*StarCategoryCheck)(undefined8,ulonglong,undefined4,undefined8) = (bool(*)(undefined8,ulonglong,undefined4,undefined8))0x161f47320;
    namespace QuestData {
      static void *ResourceVtable = (void*)0x14343a190;
      static undefined8(*ResourceFunc)() = (undefined8(*)())0x141a18ca0;
      static void *ResourcePtr = (void*)0x145062848;
    }
    namespace QuestNoList {
      static void *ResourceVtable = (void*)0x142fd5e68;
      static undefined8(*ResourceFunc)() = (undefined8(*)())0x14046f490;
      static void *ResourcePtr = (void*)0x144d0ea98;
    }
  }
  namespace Player {
    static void *BasePtr = (void*)0x14506ab70;
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x141ba12e0;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x141360810;
  }
  namespace Monster {
    static void(*dtor)(undefined8 *) = (void(*)(undefined8 *))0x141cb7750;
    static void *vptr = (void*)0x14349ee50;
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x14139b4c0;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x141cd8220;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x141cb4e70;
    namespace SoftenTimers {
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140af2830;
    }
  }
  namespace Weapon {
    namespace UI {
      static undefined8(*CalcAwakenedElement)() = (undefined8(*)())0x141985fc0;
      static uint(*CalcRawBloat)(uint,uint) = (uint(*)(uint,uint))0x141985f90;
      static void *RawBloatMultipliers = (void*)0x143408478;
      namespace Unkn {
        static undefined8(*ConditionalElementalBloat)() = (undefined8(*)())0x141922c00;
      }
      static undefined8(*CalcElementalBloat)() = (undefined8(*)())0x141985fb0;
    }
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x141a753b0;
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x1402492e0;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x1418dc2a0;
    static void *StringPtr = (void*)0x143f43f70;
  }
  namespace String {
    static undefined8(*Format__)(undefined8,undefined8,undefined8,undefined8,undefined) = (undefined8(*)(undefined8,undefined8,undefined8,undefined8,undefined))0x140461410;
    static undefined8(*Format)() = (undefined8(*)())0x140305550;
  }
  namespace Chat {
    static undefined8(*BuildShowGameMessage_)() = (undefined8(*)())0x1419ab2f0;
    static void *MainPtr = (void*)0x145064170;
    static void(*ShowGameMessage)(undefined *,undefined *,float,uint,undefined1) = (void(*)(undefined *,undefined *,float,uint,undefined1))0x141a5d0c0;
    namespace Unkn {
      static undefined8(*CallBuild)() = (undefined8(*)())0x1411b5aa0;
    }
    static undefined8(*BuildShowGameMessage)() = (undefined8(*)())0x1419ab390;
  }
  namespace Damage {
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x1402c78f0;
  }
  namespace File {
    static undefined8(*LoadResource)() = (undefined8(*)())0x142238840;
  }
  namespace QuestBoard {
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x14114bd80;
  }
}
