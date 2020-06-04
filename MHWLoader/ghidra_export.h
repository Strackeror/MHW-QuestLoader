
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
    static bool(*CanClawTurn)(longlong) = (bool(*)(longlong))0x15fb7b8f0;
    namespace EmDmg {
      static undefined *(*At)(undefined *,uint) = (undefined *(*)(undefined *,uint))0x147d77ab0;
      static ulonglong(*Count)(undefined *) = (ulonglong(*)(undefined *))0x14723adb0;
    }
    static undefined *(*GetEmDmg)(undefined *) = (undefined *(*)(undefined *))0x15fb6a1e0;
    static bool(*HasEmDmg)(undefined *) = (bool(*)(undefined *))0x15fb82af0;
    namespace SoftenBuildUp {
      static bool(*AddBuildup)(undefined8,undefined8,float) = (bool(*)(undefined8,undefined8,float))0x14729f9a0;
    }
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x1556faca0;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x15fba7570;
    static longlong(*MotionFromId)(longlong,ulonglong) = (longlong(*)(longlong,ulonglong))0x15f87ce90;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x15fb0fd00;
    namespace Hitzones {
      static undefined8(*SoftenCalc)() = (undefined8(*)())0x15134b5d0;
    }
    static undefined8(*GetHitzoneArray)() = (undefined8(*)())0x15fb6d0d0;
    namespace Unkn {
      static undefined8(*ManageEnrageTimer)() = (undefined8(*)())0x151888a70;
    }
    namespace HealthManager {
      static bool(*DealDamage)(byte *,undefined4,bool) = (bool(*)(byte *,undefined4,bool))0x154df9930;
    }
    namespace SoftenTimers {
      static bool(*IsPartSoftened)(undefined *,uint,uint) = (bool(*)(undefined *,uint,uint))0x151887c30;
      namespace Network {
        static undefined8(*WoundNotification)() = (undefined8(*)())0x151889970;
      }
      static undefined *(*WoundPart)(undefined *,uint,float) = (undefined *(*)(undefined *,uint,float))0x15188a8f0;
      static undefined *(*AddWoundTimer)(undefined *,int,float) = (undefined *(*)(undefined *,int,float))0x15188a150;
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140a5c750;
    }
    static void(*dtor)(undefined *) = (void(*)(undefined *))0x15fb14dc0;
    namespace Construct {
      static longlong(*ConstructId)(undefined8,uint,uint) = (longlong(*)(undefined8,uint,uint))0x15f3b7420;
      static undefined *(*GetConstructorFromId)(uint) = (undefined *(*)(uint))0x15572be50;
      static void *ConstructorArray = (void*)0x143e3ddf0;
      static undefined8(*ConstructId2)(undefined8,uint,uint,uint) = (undefined8(*)(undefined8,uint,uint,uint))0x15f3b93d0;
      static undefined *(*GetConstructorFromId2)(uint) = (undefined *(*)(uint))0x15572cb00;
      static void *ConstructorArray2 = (void*)0x143e3e1b0;
      static undefined8(*CreateFilePaths)() = (undefined8(*)())0x15fbcdba0;
    }
  }
  namespace Weapon {
    static undefined8(*GenerateAwakens_)() = (undefined8(*)())0x148094350;
    static undefined8(*GenerateUpgrade)() = (undefined8(*)())0x148093b50;
    static int(*GetStoredPotential)(undefined *) = (int(*)(undefined *))0x15197f6b0;
    static void(*GenerateAddAwakens)(undefined *,uint *) = (void(*)(undefined *,uint *))0x148092c10;
    static bool(*AwakenInvalid)(undefined *,undefined *,ushort,uint,int,bool) = (bool(*)(undefined *,undefined *,ushort,uint,int,bool))0x148092600;
    static int(*CalcAwakenedElement)(int,int) = (int(*)(int,int))0x15eb48850;
    static bool(*AwakenInvalidForEquip)(undefined *,undefined2) = (bool(*)(undefined *,undefined2))0x15eb53000;
  }
  namespace Player {
    static void *BasePtr = (void*)0x144f53580;
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x15f636130;
  }
  namespace Math {
    static int(*Random)(uint *) = (int(*)(uint *))0x160ed1860;
    static int(*GetCeiling)(float) = (int(*)(float))0x160d529f0;
  }
  namespace Damage {
    static bool(*FetchReactedAction)(undefined *,uint,uint,uint *) = (bool(*)(undefined *,uint,uint,uint *))0x147255c20;
    static ulonglong(*GetHitzoneValue)(longlong,uint,ulonglong,ulonglong,uint,bool) = (ulonglong(*)(longlong,uint,ulonglong,ulonglong,uint,bool))0x14725cde0;
    static void(*Apply)(undefined *,undefined *,undefined *) = (void(*)(undefined *,undefined *,undefined *))0x14726b980;
    namespace Unkn {
      static undefined8(*HandleReactionUU)() = (undefined8(*)())0x15f71e270;
      static undefined8(*HandleReactionU)() = (undefined8(*)())0x14726d5b0;
    }
    static undefined8(*OverrideReaction)() = (undefined8(*)())0x1472563c0;
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x14726cd90;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x15562cc80;
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x15f13c030;
  }
  namespace File {
    static undefined8(*NativePCCheck)(undefined,undefined,undefined,undefined,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined8))0x161176f70;
    static undefined8(*FilePathCheck)() = (undefined8(*)())0x160f50b90;
    static undefined8(*LoadResource)() = (undefined8(*)())0x16116b3a0;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x15e588870;
    static void *StringPtr = (void*)0x143e39380;
    static void *String = (void*)0x1431a60b8;
  }
  namespace String {
    static undefined8(*Format__)() = (undefined8(*)())0x147d7f140;
    namespace Unkn {
      static undefined8(*Unkn)() = (undefined8(*)())0x1611db020;
      static undefined8(*Load_)() = (undefined8(*)())0x160f17410;
    }
    static undefined8(*Format)(char *,char *) = (undefined8(*)(char *,char *))0x1473c4d50;
  }
  namespace Timer {
    static void(*Increase)(longlong) = (void(*)(longlong))0x15189b290;
    static bool(*IncreaseTimer)(undefined *,float) = (bool(*)(undefined *,float))0x1555b9640;
  }
  namespace SOBJ {
    static undefined8(*LoadSOBJs)() = (undefined8(*)())0x15f58e540;
    namespace Unkn {
      static undefined8(*CalledForEachSobj_)() = (undefined8(*)())0x1555226d0;
    }
    static undefined8(*Load)() = (undefined8(*)())0x160d52ff0;
    static undefined8(*Spawn)() = (undefined8(*)())0x160d57090;
  }
  namespace Quest {
    static undefined8(*OptionalCount)() = (undefined8(*)())0x155618fb0;
    static void *OptionalIdList = (void*)0x1431a8ec0;
    namespace Unkn {
      static bool(*Category0or7)(undefined8) = (bool(*)(undefined8))0x15e905dc0;
    }
    static undefined8(*GetCategory)() = (undefined8(*)())0x15eb19d00;
    static undefined8(*ErrorCheck_)() = (undefined8(*)())0x154ab6f80;
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x154ab73e0;
    static bool(*CheckComplete)(longlong,int) = (bool(*)(longlong,int))0x1555f4e70;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x155618d80;
    static void *GlobalOptionalQuestList = (void*)0x144f529d8;
    static ulonglong(*UnknFilterFlag)(ulonglong,uint,undefined8,undefined8) = (ulonglong(*)(ulonglong,uint,undefined8,undefined8))0x15eb1bab0;
    static bool(*StarCategoryCheck)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x1541c5580;
    static undefined8(*CheckProgress)() = (undefined8(*)())0x1555f5120;
    namespace QuestData {
      static void *ResourcePtr = (void*)0x144f4a719;
    }
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144bfa2f8;
    }
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x146fbc480;
  }
  namespace Network {
    static undefined8(*DmgPacket_)() = (undefined8(*)())0x15f7205e0;
  }
  namespace Chat {
    static void(*BuildShowGameMessage)(undefined8,uint,byte,uint) = (void(*)(undefined8,uint,byte,uint))0x15ecaa860;
    static void *MainPtr = (void*)0x144f4c040;
    static void(*ShowGameMessage)(undefined *,char *,float,uint,byte) = (void(*)(undefined *,char *,float,uint,byte))0x15f0d34a0;
  }
  namespace QuestBoard {
    static undefined8(*DisplayQuests)() = (undefined8(*)())0x154ac2ed0;
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x154ac7130;
  }
}
