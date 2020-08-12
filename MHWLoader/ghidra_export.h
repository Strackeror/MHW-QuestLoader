
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
    static bool(*CanClawTurn)(longlong) = (bool(*)(longlong))0x161003840;
    namespace EmDmg {
      static undefined *(*At)(undefined *,uint) = (undefined *(*)(undefined *,uint))0x1478defd0;
      static ulonglong(*Count)(undefined *) = (ulonglong(*)(undefined *))0x146e86950;
    }
    static undefined *(*GetEmDmg)(undefined *) = (undefined *(*)(undefined *))0x160ff79c0;
    static bool(*HasEmDmg)(undefined *) = (bool(*)(undefined *))0x16100a1d0;
    namespace SoftenBuildUp {
      static bool(*AddBuildup)(undefined8,undefined8,float) = (bool(*)(undefined8,undefined8,float))0x146edd630;
    }
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x153c75c10;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x16102e7e0;
    static longlong(*MotionFromId)(longlong,ulonglong) = (longlong(*)(longlong,ulonglong))0x160cc68e0;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x160fb7580;
    namespace Hitzones {
      static undefined8(*SoftenCalc)() = (undefined8(*)())0x14942fea0;
    }
    static undefined8(*GetHitzoneArray)() = (undefined8(*)())0x160ffa3c0;
    namespace Unkn {
      static undefined8(*ManageEnrageTimer)() = (undefined8(*)())0x1498200e0;
    }
    namespace HealthManager {
      static bool(*DealDamage)(byte *,undefined4,bool) = (bool(*)(byte *,undefined4,bool))0x14c2399a0;
    }
    namespace SoftenTimers {
      static bool(*IsPartSoftened)(undefined *,uint,uint) = (bool(*)(undefined *,uint,uint))0x14981f890;
      namespace Network {
        static undefined8(*WoundNotification)() = (undefined8(*)())0x1498205d0;
      }
      static undefined *(*WoundPart)(undefined *,uint,float) = (undefined *(*)(undefined *,uint,float))0x149820ef0;
      static undefined *(*AddWoundTimer)(undefined *,int,float) = (undefined *(*)(undefined *,int,float))0x149820bf0;
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140a94660;
    }
    static void(*dtor)(undefined *) = (void(*)(undefined *))0x160fbba50;
    namespace Construct {
      static longlong(*ConstructId)(undefined8,uint,uint) = (longlong(*)(undefined8,uint,uint))0x16098adf0;
      static undefined *(*GetConstructorFromId)(uint) = (undefined *(*)(uint))0x153c97090;
      static void *ConstructorArray = (void*)0x143e9ee70;
      static undefined8(*ConstructId2)(undefined8,uint,uint,uint) = (undefined8(*)(undefined8,uint,uint,uint))0x16098c600;
      static undefined *(*GetConstructorFromId2)(uint) = (undefined *(*)(uint))0x153c97fa0;
      static void *ConstructorArray2 = (void*)0x143e9f230;
      static undefined8(*CreateFilePaths)() = (undefined8(*)())0x1610a5df0;
    }
  }
  namespace Weapon {
    static undefined8(*GenerateAwakens_)() = (undefined8(*)())0x147bbad10;
    static undefined8(*GenerateUpgrade)() = (undefined8(*)())0x147bba8d0;
    static int(*GetStoredPotential)(undefined *) = (int(*)(undefined *))0x1498a3a70;
    static void(*GenerateAddAwakens)(undefined *,uint *) = (void(*)(undefined *,uint *))0x147bb9bb0;
    static bool(*AwakenInvalid)(undefined *,undefined *,ushort,uint,int,bool) = (bool(*)(undefined *,undefined *,ushort,uint,int,bool))0x147bb9750;
    static int(*CalcAwakenedElement)(int,int) = (int(*)(int,int))0x1600fa4c0;
    static bool(*AwakenInvalidForEquip)(undefined *,undefined2) = (bool(*)(undefined *,undefined2))0x160103280;
  }
  namespace Player {
    static void *BasePtr = (void*)0x144fbaa60;
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x160ae8d10;
  }
  namespace Math {
    static int(*Random)(uint *) = (int(*)(uint *))0x161fa3ce0;
    static int(*GetCeiling)(float) = (int(*)(float))0x161e57b10;
  }
  namespace Damage {
    static bool(*FetchReactedAction)(undefined *,uint,uint,uint *) = (bool(*)(undefined *,uint,uint,uint *))0x146e9e000;
    static ulonglong(*GetHitzoneValue)(longlong,uint,ulonglong,ulonglong,uint,bool) = (ulonglong(*)(longlong,uint,ulonglong,ulonglong,uint,bool))0x146ea3390;
    namespace Unkn {
      static undefined8(*HandleReactionUU)() = (undefined8(*)())0x160b852f0;
      static undefined8(*HandleReactionU)() = (undefined8(*)())0x146eb2970;
    }
    static undefined8(*OverrideReaction)() = (undefined8(*)())0x146e9e5a0;
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x146eb2410;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x153b98610;
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x1607862c0;
  }
  namespace File {
    static undefined8(*NativePCCheck)(undefined,undefined,undefined,undefined,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined8))0x162179ed0;
    static undefined8(*FilePathCheck)() = (undefined8(*)())0x161ff2120;
    static undefined8(*LoadResource)() = (undefined8(*)())0x16216de80;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x15fcf0bd0;
    static void *StringPtr = (void*)0x143e9a400;
    static void *String = (void*)0x1431ff088;
  }
  namespace String {
    static undefined8(*Format__)() = (undefined8(*)())0x1478e4490;
    namespace Unkn {
      static undefined8(*Unkn)() = (undefined8(*)())0x1621c3710;
      static undefined8(*Load_)() = (undefined8(*)())0x161fdb970;
    }
    static undefined8(*Format)(char *,char *) = (undefined8(*)(char *,char *))0x146fba6c0;
  }
  namespace Timer {
    static void(*Increase)(longlong) = (void(*)(longlong))0x14983aae0;
    static bool(*IncreaseTimer)(undefined *,float) = (bool(*)(undefined *,float))0x153af27b0;
  }
  namespace SOBJ {
    static undefined8(*LoadSOBJs)() = (undefined8(*)())0x160a949c0;
    namespace Unkn {
      static undefined8(*CalledForEachSobj_)() = (undefined8(*)())0x153a48bb0;
    }
    static undefined8(*Load)() = (undefined8(*)())0x161e58130;
    static undefined8(*Spawn)() = (undefined8(*)())0x161e5ba30;
  }
  namespace Quest {
    static undefined8(*OptionalCount)() = (undefined8(*)())0x153b87e30;
    static void *OptionalIdList = (void*)0x143201ec0;
    namespace Unkn {
      static bool(*Category0or7)(undefined8) = (bool(*)(undefined8))0x15ff15360;
    }
    static undefined8(*GetCategory)() = (undefined8(*)())0x1600d5b00;
    static undefined8(*ErrorCheck_)() = (undefined8(*)())0x14bf60f30;
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x14bf61210;
    static undefined8(*CheckProgress)() = (undefined8(*)())0x153b31f80;
    static bool(*CheckComplete)(longlong,int) = (bool(*)(longlong,int))0x153b31db0;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x153b87b40;
    static ulonglong(*IsMasterRank)(ulonglong,uint,undefined8,undefined8) = (ulonglong(*)(ulonglong,uint,undefined8,undefined8))0x1600d7460;
    static void *GlobalOptionalQuestList = (void*)0x144fb9ea0;
    static bool(*StarCategoryCheck)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x14b7db860;
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144c5f9c0;
    }
    namespace QuestData {
      static void *ResourcePtr = (void*)0x144fb2748;
    }
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x146c89020;
  }
  namespace Network {
    static undefined8(*DmgPacket_)() = (undefined8(*)())0x160b86800;
  }
  namespace Chat {
    static void(*BuildShowGameMessage)(undefined8,uint,byte,uint) = (void(*)(undefined8,uint,byte,uint))0x1601d8440;
    static void *MainPtr = (void*)0x144fb4070;
    static void(*ShowGameMessage)(undefined *,char *,float,uint,byte) = (void(*)(undefined *,char *,float,uint,byte))0x16070dd70;
  }
  namespace QuestBoard {
    static undefined8(*DisplayQuests)() = (undefined8(*)())0x14bf6a4e0;
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x14bf6e740;
  }
}
