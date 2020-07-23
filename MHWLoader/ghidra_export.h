
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
  namespace Monster {
    static bool(*CanClawTurn)(longlong) = (bool(*)(longlong))0x15fdbb0e0;
    namespace EmDmg {
      static undefined *(*At)(undefined *,uint) = (undefined *(*)(undefined *,uint))0x147c89fd0;
      static ulonglong(*Count)(undefined *) = (ulonglong(*)(undefined *))0x147250550;
    }
    static undefined *(*GetEmDmg)(undefined *) = (undefined *(*)(undefined *))0x15fd8dba0;
    static bool(*HasEmDmg)(undefined *) = (bool(*)(undefined *))0x15fdc10b0;
    namespace SoftenBuildUp {
      static bool(*AddBuildup)(undefined8,undefined8,float) = (bool(*)(undefined8,undefined8,float))0x1472ab6f0;
    }
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x14d0bbb90;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x15fddd370;
    static longlong(*MotionFromId)(longlong,ulonglong) = (longlong(*)(longlong,ulonglong))0x15fb0d3d0;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x15fd4afa0;
    namespace Hitzones {
      static undefined8(*SoftenCalc)() = (undefined8(*)())0x1497ce9d0;
    }
    static undefined8(*GetHitzoneArray)() = (undefined8(*)())0x15fd90fc0;
    namespace Unkn {
      static undefined8(*ManageEnrageTimer)() = (undefined8(*)())0x149c21740;
    }
    namespace HealthManager {
      static bool(*DealDamage)(byte *,undefined4,bool) = (bool(*)(byte *,undefined4,bool))0x14c93d980;
    }
    namespace SoftenTimers {
      static bool(*IsPartSoftened)(undefined *,uint,uint) = (bool(*)(undefined *,uint,uint))0x149c20460;
      namespace Network {
        static undefined8(*WoundNotification)() = (undefined8(*)())0x149c21e60;
      }
      static undefined *(*WoundPart)(undefined *,uint,float) = (undefined *(*)(undefined *,uint,float))0x149c22830;
      static undefined *(*AddWoundTimer)(undefined *,int,float) = (undefined *(*)(undefined *,int,float))0x149c224e0;
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140a94660;
    }
    static void(*dtor)(undefined *) = (void(*)(undefined *))0x15fd4f210;
    namespace Construct {
      static longlong(*ConstructId)(undefined8,uint,uint) = (longlong(*)(undefined8,uint,uint))0x15f77c950;
      static undefined *(*GetConstructorFromId)(uint) = (undefined *(*)(uint))0x14d1036b0;
      static void *ConstructorArray = (void*)0x143e9ee70;
      static undefined8(*ConstructId2)(undefined8,uint,uint,uint) = (undefined8(*)(undefined8,uint,uint,uint))0x15f77e030;
      static undefined *(*GetConstructorFromId2)(uint) = (undefined *(*)(uint))0x14d104090;
      static void *ConstructorArray2 = (void*)0x143e9f230;
      static undefined8(*CreateFilePaths)() = (undefined8(*)())0x15fdff6d0;
    }
  }
  namespace Weapon {
    static undefined8(*GenerateAwakens_)() = (undefined8(*)())0x147ee2c10;
    static undefined8(*GenerateUpgrade)() = (undefined8(*)())0x147ee2650;
    static int(*GetStoredPotential)(undefined *) = (int(*)(undefined *))0x149d54910;
    static void(*GenerateAddAwakens)(undefined *,uint *) = (void(*)(undefined *,uint *))0x147ee1de0;
    static bool(*AwakenInvalid)(undefined *,undefined *,ushort,uint,int,bool) = (bool(*)(undefined *,undefined *,ushort,uint,int,bool))0x147ee18f0;
    static int(*CalcAwakenedElement)(int,int) = (int(*)(int,int))0x15f005ff0;
    static bool(*AwakenInvalidForEquip)(undefined *,undefined2) = (bool(*)(undefined *,undefined2))0x15f00eab0;
  }
  namespace Player {
    static void *BasePtr = (void*)0x144fbaa60;
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x15f95c1c0;
  }
  namespace Math {
    static int(*Random)(uint *) = (int(*)(uint *))0x160d81960;
    static int(*GetCeiling)(float) = (int(*)(float))0x160c42a90;
  }
  namespace Damage {
    static bool(*FetchReactedAction)(undefined *,uint,uint,uint *) = (bool(*)(undefined *,uint,uint,uint *))0x147269830;
    static ulonglong(*GetHitzoneValue)(longlong,uint,ulonglong,ulonglong,uint,bool) = (ulonglong(*)(longlong,uint,ulonglong,ulonglong,uint,bool))0x14726ee30;
    namespace Unkn {
      static undefined8(*HandleReactionUU)() = (undefined8(*)())0x15f9db690;
      static undefined8(*HandleReactionU)() = (undefined8(*)())0x14727ec30;
    }
    static undefined8(*OverrideReaction)() = (undefined8(*)())0x147269d10;
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x14727e2c0;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x14cfd6800;
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x15f4cba90;
  }
  namespace File {
    static undefined8(*NativePCCheck)(undefined,undefined,undefined,undefined,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined8))0x160f11d30;
    static undefined8(*FilePathCheck)() = (undefined8(*)())0x160dd9ec0;
    static undefined8(*LoadResource)() = (undefined8(*)())0x160f06620;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x15ebd31c0;
    static void *StringPtr = (void*)0x143e9a400;
    static void *String = (void*)0x1431ff088;
  }
  namespace String {
    static undefined8(*Format__)() = (undefined8(*)())0x147c8f6e0;
    namespace Unkn {
      static undefined8(*Unkn)() = (undefined8(*)())0x160f58fb0;
      static undefined8(*Load_)() = (undefined8(*)())0x160dc0fc0;
    }
    static undefined8(*Format)(char *,char *) = (undefined8(*)(char *,char *))0x1473b46c0;
  }
  namespace Timer {
    static void(*Increase)(longlong) = (void(*)(longlong))0x149c30b20;
    static bool(*IncreaseTimer)(undefined *,float) = (bool(*)(undefined *,float))0x14cf33150;
  }
  namespace SOBJ {
    static undefined8(*LoadSOBJs)() = (undefined8(*)())0x15f907330;
    namespace Unkn {
      static undefined8(*CalledForEachSobj_)() = (undefined8(*)())0x14cec8eb0;
    }
    static undefined8(*Load)() = (undefined8(*)())0x160c42e40;
    static undefined8(*Spawn)() = (undefined8(*)())0x160c462d0;
  }
  namespace Quest {
    static undefined8(*OptionalCount)() = (undefined8(*)())0x14cfc5b20;
    static void *OptionalIdList = (void*)0x143201ec0;
    namespace Unkn {
      static bool(*Category0or7)(undefined8) = (bool(*)(undefined8))0x15ee3fb10;
    }
    static undefined8(*GetCategory)() = (undefined8(*)())0x15efe0f10;
    static undefined8(*ErrorCheck_)() = (undefined8(*)())0x14c66de40;
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x14c66e1e0;
    static bool(*CheckComplete)(longlong,int) = (bool(*)(longlong,int))0x14cfa66e0;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x14cfc5910;
    static void *GlobalOptionalQuestList = (void*)0x144fb9ea0;
    static ulonglong(*IsMasterRank)(ulonglong,uint,undefined8,undefined8) = (ulonglong(*)(ulonglong,uint,undefined8,undefined8))0x15efe3120;
    static bool(*StarCategoryCheck)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x14bda3600;
    static undefined8(*CheckProgress)() = (undefined8(*)())0x14cfa6a30;
    namespace QuestData {
      static void *ResourcePtr = (void*)0x144fb2748;
    }
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144c5f9c0;
    }
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x146d964e0;
  }
  namespace Network {
    static undefined8(*DmgPacket_)() = (undefined8(*)())0x15f9dd950;
  }
  namespace Chat {
    static void(*BuildShowGameMessage)(undefined8,uint,byte,uint) = (void(*)(undefined8,uint,byte,uint))0x15f186fd0;
    static void *MainPtr = (void*)0x144fb4070;
    static void(*ShowGameMessage)(undefined *,char *,float,uint,byte) = (void(*)(undefined *,char *,float,uint,byte))0x15f46e3b0;
  }
  namespace QuestBoard {
    static undefined8(*DisplayQuests)() = (undefined8(*)())0x14c6763c0;
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x14c67a450;
  }
}
