
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
    static bool(*CanClawTurn)(longlong) = (bool(*)(longlong))0x160230ca0;
    namespace EmDmg {
      static undefined *(*At)(undefined *,uint) = (undefined *(*)(undefined *,uint))0x147db9020;
      static ulonglong(*Count)(undefined *) = (ulonglong(*)(undefined *))0x147239d10;
    }
    static undefined *(*GetEmDmg)(undefined *) = (undefined *(*)(undefined *))0x1601e19b0;
    static bool(*HasEmDmg)(undefined *) = (bool(*)(undefined *))0x1602383d0;
    namespace SoftenBuildUp {
      static bool(*AddBuildup)(undefined8,undefined8,float) = (bool(*)(undefined8,undefined8,float))0x147292f80;
    }
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x14d7ef370;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x160262f70;
    static longlong(*MotionFromId)(longlong,ulonglong) = (longlong(*)(longlong,ulonglong))0x1584aa3c0;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x16019c2c0;
    namespace Hitzones {
      static undefined8(*SoftenCalc)() = (undefined8(*)())0x149989e30;
    }
    static undefined8(*GetHitzoneArray)() = (undefined8(*)())0x1601e4ae0;
    namespace Unkn {
      static undefined8(*ManageEnrageTimer)() = (undefined8(*)())0x149e58d60;
    }
    namespace HealthManager {
      static bool(*DealDamage)(byte *,undefined4,bool) = (bool(*)(byte *,undefined4,bool))0x14d11e0e0;
    }
    namespace SoftenTimers {
      static bool(*IsPartSoftened)(undefined *,uint,uint) = (bool(*)(undefined *,uint,uint))0x149e58810;
      namespace Network {
        static undefined8(*WoundNotification)() = (undefined8(*)())0x149e593d0;
      }
      static undefined *(*WoundPart)(undefined *,uint,float) = (undefined *(*)(undefined *,uint,float))0x149e59af0;
      static undefined *(*AddWoundTimer)(undefined *,int,float) = (undefined *(*)(undefined *,int,float))0x149e59840;
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140a94660;
    }
    static void(*dtor)(undefined *) = (void(*)(undefined *))0x16019fe60;
    namespace Construct {
      static longlong(*ConstructId)(undefined8,uint,uint) = (longlong(*)(undefined8,uint,uint))0x1580b16c0;
      static undefined *(*GetConstructorFromId)(uint) = (undefined *(*)(uint))0x14d835260;
      static void *ConstructorArray = (void*)0x143e9ee70;
      static undefined8(*ConstructId2)(undefined8,uint,uint,uint) = (undefined8(*)(undefined8,uint,uint,uint))0x1580b3130;
      static undefined *(*GetConstructorFromId2)(uint) = (undefined *(*)(uint))0x14d835fa0;
      static void *ConstructorArray2 = (void*)0x143e9f230;
      static undefined8(*CreateFilePaths)() = (undefined8(*)())0x160284eb0;
    }
  }
  namespace Weapon {
    static undefined8(*GenerateAwakens_)() = (undefined8(*)())0x14809f380;
    static undefined8(*GenerateUpgrade)() = (undefined8(*)())0x14809efc0;
    static int(*GetStoredPotential)(undefined *) = (int(*)(undefined *))0x149f223b0;
    static void(*GenerateAddAwakens)(undefined *,uint *) = (void(*)(undefined *,uint *))0x14809e380;
    static bool(*AwakenInvalid)(undefined *,undefined *,ushort,uint,int,bool) = (bool(*)(undefined *,undefined *,ushort,uint,int,bool))0x14809d4f0;
    static int(*CalcAwakenedElement)(int,int) = (int(*)(int,int))0x1504dec10;
    static bool(*AwakenInvalidForEquip)(undefined *,undefined2) = (bool(*)(undefined *,undefined2))0x1504ebfb0;
  }
  namespace Player {
    static void *BasePtr = (void*)0x144fbaa60;
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x15825d740;
  }
  namespace Math {
    static int(*Random)(uint *) = (int(*)(uint *))0x16145cd80;
    static int(*GetCeiling)(float) = (int(*)(float))0x1612d7b80;
  }
  namespace Damage {
    static bool(*FetchReactedAction)(undefined *,uint,uint,uint *) = (bool(*)(undefined *,uint,uint,uint *))0x147251270;
    static ulonglong(*GetHitzoneValue)(longlong,uint,ulonglong,ulonglong,uint,bool) = (ulonglong(*)(longlong,uint,ulonglong,ulonglong,uint,bool))0x1472565e0;
    namespace Unkn {
      static undefined8(*HandleReactionUU)() = (undefined8(*)())0x1582e28c0;
      static undefined8(*HandleReactionU)() = (undefined8(*)())0x147265710;
    }
    static undefined8(*OverrideReaction)() = (undefined8(*)())0x1472518f0;
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x1472651a0;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x14d6742b0;
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x150a42b20;
  }
  namespace File {
    static undefined8(*NativePCCheck)(undefined,undefined,undefined,undefined,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined8))0x161607f80;
    static undefined8(*FilePathCheck)() = (undefined8(*)())0x1614bbbb0;
    static undefined8(*LoadResource)() = (undefined8(*)())0x1615fc710;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x1500f0910;
    static void *StringPtr = (void*)0x143e9a400;
    static void *String = (void*)0x1431ff088;
  }
  namespace String {
    static undefined8(*Format__)() = (undefined8(*)())0x147dbf750;
    namespace Unkn {
      static undefined8(*Unkn)() = (undefined8(*)())0x1616675b0;
      static undefined8(*Load_)() = (undefined8(*)())0x1614a4410;
    }
    static undefined8(*Format)(char *,char *) = (undefined8(*)(char *,char *))0x1473901a0;
  }
  namespace Timer {
    static void(*Increase)(longlong) = (void(*)(longlong))0x149e764f0;
    static bool(*IncreaseTimer)(undefined *,float) = (bool(*)(undefined *,float))0x14d609210;
  }
  namespace SOBJ {
    static undefined8(*LoadSOBJs)() = (undefined8(*)())0x158208d20;
    namespace Unkn {
      static undefined8(*CalledForEachSobj_)() = (undefined8(*)())0x14d572aa0;
    }
    static undefined8(*Load)() = (undefined8(*)())0x1612d7f90;
    static undefined8(*Spawn)() = (undefined8(*)())0x1612dc0f0;
  }
  namespace Quest {
    static undefined8(*OptionalCount)() = (undefined8(*)())0x14d6632b0;
    static void *OptionalIdList = (void*)0x143201ec0;
    namespace Unkn {
      static bool(*Category0or7)(undefined8) = (bool(*)(undefined8))0x15039f0e0;
    }
    static undefined8(*GetCategory)() = (undefined8(*)())0x1504ba770;
    static undefined8(*ErrorCheck_)() = (undefined8(*)())0x14ce245a0;
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x14ce24960;
    static bool(*CheckComplete)(longlong,int) = (bool(*)(longlong,int))0x14d63e3f0;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x14d662ed0;
    static void *GlobalOptionalQuestList = (void*)0x144fb9ea0;
    static ulonglong(*IsMasterRank)(ulonglong,uint,undefined8,undefined8) = (ulonglong(*)(ulonglong,uint,undefined8,undefined8))0x1504bc1c0;
    static bool(*StarCategoryCheck)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x14c47dc80;
    static undefined8(*CheckProgress)() = (undefined8(*)())0x14d63e5a0;
    namespace QuestData {
      static void *ResourcePtr = (void*)0x144fb2748;
    }
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144c5f9c0;
    }
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x146ffe280;
  }
  namespace Network {
    static undefined8(*DmgPacket_)() = (undefined8(*)())0x1582e4000;
  }
  namespace Chat {
    static void(*BuildShowGameMessage)(undefined8,uint,byte,uint) = (void(*)(undefined8,uint,byte,uint))0x15074b370;
    static void *MainPtr = (void*)0x144fb4070;
    static void(*ShowGameMessage)(undefined *,char *,float,uint,byte) = (void(*)(undefined *,char *,float,uint,byte))0x1509e5a00;
  }
  namespace QuestBoard {
    static undefined8(*DisplayQuests)() = (undefined8(*)())0x14ce2dbb0;
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x14ce32080;
  }
}
