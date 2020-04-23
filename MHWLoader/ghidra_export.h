
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
    static bool(*CanClawTurn)(longlong) = (bool(*)(longlong))0x15ef0fe40;
    namespace EmDmg {
      static undefined *(*At)(undefined *,uint) = (undefined *(*)(undefined *,uint))0x1477dbb90;
      static ulonglong(*Count)(undefined *) = (ulonglong(*)(undefined *))0x146fc1450;
    }
    static undefined *(*GetEmDmg)(undefined *) = (undefined *(*)(undefined *))0x15eef5280;
    static bool(*HasEmDmg)(undefined *) = (bool(*)(undefined *))0x15ef16d40;
    namespace SoftenBuildUp {
      static bool(*AddBuildup)(undefined8,undefined8,float) = (bool(*)(undefined8,undefined8,float))0x147014030;
    }
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x1548b2c60;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x141c27810;
    static longlong(*MotionFromId)(longlong,ulonglong) = (longlong(*)(longlong,ulonglong))0x15ec8e010;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x15eeb46f0;
    namespace Hitzones {
      static undefined8(*SoftenCalc)() = (undefined8(*)())0x14928c400;
    }
    static undefined8(*GetHitzoneArray)() = (undefined8(*)())0x15ef06990;
    namespace Unkn {
      static undefined8(*ManageEnrageTimer)() = (undefined8(*)())0x149681b70;
    }
    namespace HealthManager {
      static bool(*DealDamage)(byte *,undefined4,bool) = (bool(*)(byte *,undefined4,bool))0x1541d5780;
    }
    namespace SoftenTimers {
      static bool(*IsPartSoftened)(undefined *,uint,uint) = (bool(*)(undefined *,uint,uint))0x149681450;
      static undefined *(*AddWoundTimer)(undefined *,int,float) = (undefined *(*)(undefined *,int,float))0x1496829b0;
      static undefined *(*WoundPart)(undefined *,uint,float) = (undefined *(*)(undefined *,uint,float))0x149682f20;
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140a5c750;
      namespace Network {
        static undefined8(*WoundNotification)() = (undefined8(*)())0x1496821a0;
      }
    }
    static void(*dtor)(undefined *) = (void(*)(undefined *))0x15eeb7f90;
    namespace Construct {
      static longlong(*ConstructId)(undefined8,uint,uint) = (longlong(*)(undefined8,uint,uint))0x15e743660;
      static undefined8(*ConstructId2)(undefined8,uint,uint,uint) = (undefined8(*)(undefined8,uint,uint,uint))0x15e745120;
      static undefined8(*CreateFilePaths)() = (undefined8(*)())0x15ef507b0;
    }
  }
  namespace Weapon {
    static undefined8(*GenerateAwakens_)() = (undefined8(*)())0x147a39ec0;
    static undefined8(*GenerateUpgrade)() = (undefined8(*)())0x147a39a60;
    static int(*GetStoredPotential)(undefined *) = (int(*)(undefined *))0x1497bd010;
    static void(*GenerateAddAwakens)(undefined *,uint *) = (void(*)(undefined *,uint *))0x147a394b0;
    static bool(*AwakenInvalid)(undefined *,undefined *,ushort,uint,int,bool) = (bool(*)(undefined *,undefined *,ushort,uint,int,bool))0x147a39090;
    static bool(*AwakenInvalidForEquip)(undefined *,undefined2) = (bool(*)(undefined *,undefined2))0x15e0166c0;
    static int(*CalcAwakenedElement)(int,int) = (int(*)(int,int))0x15e00deb0;
  }
  namespace Player {
    static void *BasePtr = (void*)0x144f54590;
    static undefined *(*GetPlayer)(undefined *) = (undefined *(*)(undefined *))0x15e8a3d00;
  }
  namespace Math {
    static int(*Random)(uint *) = (int(*)(uint *))0x15fe1f8b0;
    static int(*GetCeiling)(float) = (int(*)(float))0x15fce5fb0;
  }
  namespace Damage {
    static bool(*FetchReactedAction)(undefined *,uint,uint,uint *) = (bool(*)(undefined *,uint,uint,uint *))0x146fd5a80;
    static ulonglong(*GetHitzoneValue)(longlong,uint,ulonglong,ulonglong,uint,bool) = (ulonglong(*)(longlong,uint,ulonglong,ulonglong,uint,bool))0x146fdab40;
    static undefined8(*OverrideReaction)() = (undefined8(*)())0x146fd5f10;
    static void(*Apply)(undefined *,undefined *,undefined *) = (void(*)(undefined *,undefined *,undefined *))0x146fe7fc0;
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x146fe9620;
    namespace Unkn {
      static undefined8(*HandleReactionUU)() = (undefined8(*)())0x15e918550;
      static undefined8(*HandleReactionU)() = (undefined8(*)())0x146fe9b90;
    }
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x15480b640;
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x15e488ea0;
  }
  namespace File {
    static undefined8(*FilePathCheck)() = (undefined8(*)())0x15fe6e150;
    static undefined8(*NativePCCheck)(undefined,undefined,undefined,undefined,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined8))0x15ffa1ee0;
    static undefined8(*LoadResource)() = (undefined8(*)())0x15ff970d0;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x156c054e0;
    static void *StringPtr = (void*)0x143e3a380;
  }
  namespace Timer {
    static bool(*IncreaseTimer)(undefined *,float) = (bool(*)(undefined *,float))0x1547ae620;
    static void(*Increase)(longlong) = (void(*)(longlong))0x1496a17b0;
  }
  namespace SOBJ {
    static undefined8(*LoadSOBJs)() = (undefined8(*)())0x15e82f970;
    namespace Unkn {
      static undefined8(*CalledForEachSobj_)() = (undefined8(*)())0x15471ee60;
    }
    static undefined8(*Load)() = (undefined8(*)())0x15fce6540;
    static undefined8(*Spawn)() = (undefined8(*)())0x142057e70;
  }
  namespace String {
    static undefined8(*Format__)() = (undefined8(*)())0x1477e0b40;
    namespace Unkn {
      static undefined8(*Unkn)() = (undefined8(*)())0x15ffe59b0;
      static undefined8(*Load_)() = (undefined8(*)())0x15fe57cb0;
    }
  }
  namespace Quest {
    static bool(*CheckComplete)(undefined *,uint) = (bool(*)(undefined *,uint))0x1547e0160;
    static undefined8(*CheckProgress)() = (undefined8(*)())0x1547e08f0;
    static undefined8(*GetCategory)() = (undefined8(*)())0x15dfec370;
    static void(*UnknFilterFlag)(undefined8,undefined8,undefined8) = (void(*)(undefined8,undefined8,undefined8))0x15dfedef0;
    static undefined8(*OptionalCount)() = (undefined8(*)())0x1547fc340;
    static void *OptionalIdList = (void*)0x1431a9ec0;
    namespace Unkn {
      static bool(*Category0or7)(undefined8) = (bool(*)(undefined8))0x15dee0130;
    }
    static undefined8(*ErrorCheck_)() = (undefined8(*)())0x153f04fb0;
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x153f053c0;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x1547fc250;
    static void *GlobalOptionalQuestList = (void*)0x144f539e8;
    static bool(*StarCategoryCheck)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x14b5c9710;
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144bfb2f8;
    }
    namespace QuestData {
      static void *ResourcePtr = (void*)0x144f4b718;
    }
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x146dfb4f0;
  }
  namespace Network {
    static undefined8(*DmgPacket_)() = (undefined8(*)())0x15e91a010;
  }
  namespace Chat {
    static void(*ShowGameMessage)(undefined *,char *,float,uint,byte) = (void(*)(undefined *,char *,float,uint,byte))0x15e433920;
    static void(*BuildShowGameMessage)(undefined8,uint,byte,uint) = (void(*)(undefined8,uint,byte,uint))0x15e0e8c70;
    static void *MainPtr = (void*)0x144f4d040;
  }
  namespace QuestBoard {
    static undefined8(*DisplayQuests)() = (undefined8(*)())0x153f100f0;
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x153f13b80;
  }
}
