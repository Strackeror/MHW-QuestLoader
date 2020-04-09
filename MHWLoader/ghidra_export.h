
#pragma once
typedef unsigned char undefined; 
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef unsigned char byte; 
typedef unsigned long long ulonglong;
typedef long long longlong;
typedef unsigned int uint;

namespace MH {
  namespace Monster {
    static bool(*CanClawTurn)(longlong) = (bool(*)(longlong))0x1638b0140;
    namespace EmDmg {
      static undefined *(*At)(undefined *,uint) = (undefined *(*)(undefined *,uint))0x14809b7b0;
      static ulonglong(*Count)(undefined *) = (ulonglong(*)(undefined *))0x1474fa7f0;
    }
    static undefined *(*GetEmDmg)(undefined *) = (undefined *(*)(undefined *))0x16389f9a0;
    static bool(*HasEmDmg)(undefined *) = (bool(*)(undefined *))0x1638b90e0;
    namespace SoftenBuildUp {
      static bool(*AddBuildup)(undefined8,undefined8,float) = (bool(*)(undefined8,undefined8,float))0x14755bb00;
    }
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x15f5c15d0;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x1638e0b40;
    static longlong(*MotionFromId)(longlong,ulonglong) = (longlong(*)(longlong,ulonglong))0x163566490;
    namespace Hitzones {
      static undefined8(*SoftenCalc)() = (undefined8(*)())0x14a2a6a40;
    }
    static undefined8(*GetHitzoneArray)() = (undefined8(*)())0x1638a3370;
    namespace Unkn {
      static undefined8(*ManageEnrageTimer)() = (undefined8(*)())0x14a6a5520;
    }
    namespace HealthManager {
      static bool(*DealDamage)(byte *,undefined4,bool) = (bool(*)(byte *,undefined4,bool))0x15eb142d0;
    }
    namespace SoftenTimers {
      namespace Network {
        static undefined8(*WoundNotification)() = (undefined8(*)())0x14a6a5cc0;
      }
      static undefined *(*WoundPart)(undefined *,uint,float) = (undefined *(*)(undefined *,uint,float))0x14a6a65b0;
      static undefined *(*AddWoundTimer)(undefined *,int,float) = (undefined *(*)(undefined *,int,float))0x14a6a6290;
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140a50c20;
      static bool(*IsPartSoftened)(undefined *,uint,uint) = (bool(*)(undefined *,uint,uint))0x14a6a48c0;
    }
    static void(*dtor)(undefined *) = (void(*)(undefined *))0x163836aa0;
    namespace Construct {
      static longlong(*ConstructId)(undefined8,uint,uint) = (longlong(*)(undefined8,uint,uint))0x16314a6c0;
      static undefined *(*GetConstructorFromId)(uint) = (undefined *(*)(uint))0x15f6578e0;
      static void *ConstructorArray = (void*)0x143e1a470;
      static undefined8(*ConstructId2)(undefined8,uint,uint,uint) = (undefined8(*)(undefined8,uint,uint,uint))0x16314d5e0;
      static undefined *(*GetConstructorFromId2)(uint) = (undefined *(*)(uint))0x15f658c00;
      static void *ConstructorArray2 = (void*)0x143e1a830;
      static undefined8(*CreateFilePaths)() = (undefined8(*)())0x163905d20;
    }
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x1638324a0;
  }
  namespace Damage {
    static bool(*FetchReactedAction)(undefined *,uint,uint,uint *) = (bool(*)(undefined *,uint,uint,uint *))0x147511e10;
    static ulonglong(*GetHitzoneValue)(longlong,uint,ulonglong,ulonglong,uint,bool) = (ulonglong(*)(longlong,uint,ulonglong,ulonglong,uint,bool))0x147517d30;
    namespace Unkn {
      static undefined8(*HandleReactionUU)() = (undefined8(*)())0x1633c4dc0;
      static undefined8(*HandleReactionU)() = (undefined8(*)())0x147528990;
    }
    static undefined8(*OverrideReaction)() = (undefined8(*)())0x1475123d0;
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x147528300;
    static void(*Apply)(undefined *,undefined *,undefined *) = (void(*)(undefined *,undefined *,undefined *))0x147526b70;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x15f4c2600;
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x162e46ad0;
  }
  namespace File {
    static undefined8(*NativePCCheck)(undefined,undefined,undefined,undefined,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined8))0x164e276f0;
    static undefined8(*FilePathCheck)() = (undefined8(*)())0x164c2f4e0;
    static undefined8(*LoadResource)() = (undefined8(*)())0x164e1aa50;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x16248ccf0;
    static void *StringPtr = (void*)0x143e15a00;
  }
  namespace String {
    static undefined8(*Format__)() = (undefined8(*)())0x1480a25e0;
    namespace Unkn {
      static undefined8(*Unkn)() = (undefined8(*)())0x164e98580;
      static undefined8(*Load_)() = (undefined8(*)())0x164c13f90;
    }
    static undefined8(*Format)(char *,char *) = (undefined8(*)(char *,char *))0x147744e90;
  }
  namespace Timer {
    static void(*Increase)(longlong) = (void(*)(longlong))0x14a6c25a0;
    static bool(*IncreaseTimer)(undefined *,float) = (bool(*)(undefined *,float))0x15f3b61c0;
  }
  namespace SOBJ {
    static undefined8(*LoadSOBJs)() = (undefined8(*)())0x1632bbbb0;
    namespace Unkn {
      static undefined8(*CalledForEachSobj_)() = (undefined8(*)())0x15f33e090;
    }
    static undefined8(*Load)() = (undefined8(*)())0x1649a5370;
    static undefined8(*Spawn)() = (undefined8(*)())0x1649a8320;
  }
  namespace Quest {
    static undefined8(*OptionalCount)() = (undefined8(*)())0x15f4b2ab0;
    static void *OptionalIdList = (void*)0x143188a70;
    namespace Unkn {
      static bool(*Category0or7)(undefined8) = (bool(*)(undefined8))0x16271e990;
    }
    static undefined8(*GetCategory)() = (undefined8(*)())0x1628d0780;
    static undefined8(*ErrorCheck_)() = (undefined8(*)())0x15e74e920;
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x15e74eb70;
    static bool(*CheckComplete)(longlong,int) = (bool(*)(longlong,int))0x15f3e5e80;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x15f4b2840;
    static void *GlobalOptionalQuestList = (void*)0x144f2df58;
    static ulonglong(*UnknFilterFlag)(ulonglong,uint,undefined8,undefined8) = (ulonglong(*)(ulonglong,uint,undefined8,undefined8))0x1628d2360;
    static bool(*StarCategoryCheck)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x14cfbb270;
    namespace QuestData {
      static void *ResourcePtr = (void*)0x144f25ca8;
    }
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144bd65b0;
    }
    static bool(*CheckProgress)(longlong,uint) = (bool(*)(longlong,uint))0x15f3e6080;
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x1472a3790;
  }
  namespace Network {
    static undefined8(*DmgPacket_)() = (undefined8(*)())0x1633c6b50;
  }
  namespace Chat {
    static void(*BuildShowGameMessage)(undefined8,uint,byte,uint) = (void(*)(undefined8,uint,byte,uint))0x162a07420;
    static void *MainPtr = (void*)0x144f275d0;
    static void(*ShowGameMessage)(undefined *,char *,float,uint,byte) = (void(*)(undefined *,char *,float,uint,byte))0x162dc2a00;
  }
  namespace QuestBoard {
    static undefined8(*DisplayQuests)() = (undefined8(*)())0x15e75a100;
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x15e75e730;
  }
}
