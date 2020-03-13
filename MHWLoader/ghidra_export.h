
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
    static bool(*CanClawTurn)(longlong) = (bool(*)(longlong))0x15d011430;
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x159e3dfe0;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x15d031a50;
    static longlong(*MotionFromId)(longlong,ulonglong) = (longlong(*)(longlong,ulonglong))0x15cdcd350;
    namespace Unkn {
      static undefined8(*ManageEnrageTimer)() = (undefined8(*)())0x156eee280;
    }
    namespace SoftenTimers {
      static bool(*IsPartSoftened)(undefined *,uint,uint) = (bool(*)(undefined *,uint,uint))0x156eedd50;
      namespace Network {
        static undefined8(*WoundNotification)() = (undefined8(*)())0x156eee660;
      }
      static undefined *(*WoundPart)(undefined *,uint,float) = (undefined *(*)(undefined *,uint,float))0x156eeec40;
      static undefined *(*AddWoundTimer)(undefined *,int,float) = (undefined *(*)(undefined *,int,float))0x156eee890;
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140a21300;
    }
    static void(*dtor)(undefined *) = (void(*)(undefined *))0x15cfcc090;
    namespace Construct {
      static longlong(*ConstructId)(undefined8,uint,uint) = (longlong(*)(undefined8,uint,uint))0x15caf22c0;
      static undefined *(*GetConstructorFromId)(uint) = (undefined *(*)(uint))0x159e600f0;
      static void *ConstructorArray = (void*)0x143dbe240;
      static undefined8(*ConstructId2)(undefined8,uint,uint,uint) = (undefined8(*)(undefined8,uint,uint,uint))0x15caf3d30;
      static undefined *(*GetConstructorFromId2)(uint) = (undefined *(*)(uint))0x159e609c0;
      static void *ConstructorArray2 = (void*)0x143dbe600;
      static undefined8(*CreateFilePaths)() = (undefined8(*)())0x15d04f8c0;
    }
    namespace SoftenBuildUp {
      static bool(*AddBuildup)(undefined8,undefined8,float) = (bool(*)(undefined8,undefined8,float))0x14e722a80;
    }
    namespace Hitzones {
      static undefined8(*SoftenCalc)() = (undefined8(*)())0x156ad1850;
    }
    static undefined8(*GetHitzoneArray)() = (undefined8(*)())0x15d008370;
    namespace HealthManager {
      static bool(*DealDamage)(byte *,undefined4,bool) = (bool(*)(byte *,undefined4,bool))0x1597fdf50;
    }
    namespace EmDmg {
      static undefined *(*At)(undefined *,uint) = (undefined *(*)(undefined *,uint))0x14ed444e0;
      static ulonglong(*Count)(undefined *) = (ulonglong(*)(undefined *))0x14e6b10d0;
    }
    static undefined *(*GetEmDmg)(undefined *) = (undefined *(*)(undefined *))0x15d005d20;
    static bool(*HasEmDmg)(undefined *) = (bool(*)(undefined *))0x15d016450;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x15cfc8240;
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x15c8d5420;
  }
  namespace File {
    static undefined8(*NativePCCheck)(undefined,undefined,undefined,undefined,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined8))0x15e36e180;
    static undefined8(*FilePathCheck)() = (undefined8(*)())0x15e2279b0;
    static undefined8(*LoadResource)() = (undefined8(*)())0x15e364e40;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x15bfe72e0;
    static void *StringPtr = (void*)0x143db97d0;
    static void *String = (void*)0x143132868;
  }
  namespace String {
    static undefined8(*Format__)() = (undefined8(*)())0x14ed48dc0;
    static undefined8(*Format)(char *,char *) = (undefined8(*)(char *,char *))0x14e7d81e0;
    namespace Unkn {
      static undefined8(*Unkn)() = (undefined8(*)())0x15e3aedf0;
      static undefined8(*Load_)() = (undefined8(*)())0x15e212cc0;
    }
  }
  namespace Timer {
    static void(*Increase)(longlong) = (void(*)(longlong))0x156f0b4a0;
    static bool(*IncreaseTimer)(undefined *,float) = (bool(*)(undefined *,float))0x159ca06d0;
  }
  namespace SOBJ {
    static undefined8(*LoadSOBJs)() = (undefined8(*)())0x15cbe7290;
    namespace Unkn {
      static undefined8(*CalledForEachSobj_)() = (undefined8(*)())0x159c36b50;
    }
    static undefined8(*Load)() = (undefined8(*)())0x15e0716e0;
    static undefined8(*Spawn)() = (undefined8(*)())0x15e074470;
  }
  namespace Damage {
    static undefined8(*Handling)() = (undefined8(*)())0x14e6d9980;
    static undefined8(*CalculateDamage)(undefined,undefined,undefined,undefined,undefined4,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined4,undefined8))0x14e6c1c80;
    static void(*Apply)(undefined *,undefined *,undefined *) = (void(*)(undefined *,undefined *,undefined *))0x14e6fd1b0;
    static void(*LoadBaseVals)(undefined *,undefined *,undefined *) = (void(*)(undefined *,undefined *,undefined *))0x14e6d5150;
    namespace Unkn {
      static undefined8(*HandleReactionUU)() = (undefined8(*)())0x15cca62c0;
      static undefined8(*HandleReactionU)() = (undefined8(*)())0x14e6fec40;
    }
    static ulonglong(*GetHitzoneValue)(longlong,uint,ulonglong,ulonglong,uint,bool) = (ulonglong(*)(longlong,uint,ulonglong,ulonglong,uint,bool))0x14e6d2870;
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x14e6fe6b0;
    static bool(*FetchReactedAction)(undefined *,uint,uint,uint *) = (bool(*)(undefined *,uint,uint,uint *))0x14e6c53f0;
    static undefined8(*OverrideReaction)() = (undefined8(*)())0x14e6c5740;
  }
  namespace Quest {
    static undefined8(*OptionalCount)() = (undefined8(*)())0x159d3faa0;
    static void *OptionalIdList = (void*)0x143135680;
    namespace Unkn {
      static bool(*Category0or7)(undefined8) = (bool(*)(undefined8))0x15c2383f0;
    }
    static undefined8(*GetCategory)() = (undefined8(*)())0x15c39ccd0;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x159d3f970;
    static void *GlobalOptionalQuestList = (void*)0x144ec9cf0;
    static bool(*StarCategoryCheck)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x158e4ea30;
    static ulonglong(*UnknFilterFlag)(ulonglong,uint,undefined8,undefined8) = (ulonglong(*)(ulonglong,uint,undefined8,undefined8))0x15c39e450;
    static bool(*CheckComplete)(longlong,int) = (bool(*)(longlong,int))0x159cc4d50;
    static undefined8(*ErrorCheck_)() = (undefined8(*)())0x159552e20;
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x159553180;
    static bool(*CheckProgress)(longlong,int) = (bool(*)(longlong,int))0x159cc4e60;
    namespace QuestData {
      static void *ResourcePtr = (void*)0x144ec1d48;
    }
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144b77bb0;
    }
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x14e4eb5e0;
  }
  namespace Chat {
    static void(*BuildShowGameMessage)(undefined8,uint,byte,uint) = (void(*)(undefined8,uint,byte,uint))0x15c59b110;
    static void *MainPtr = (void*)0x144ec3670;
    static void(*ShowGameMessage)(undefined *,char *,float,uint,byte) = (void(*)(undefined *,char *,float,uint,byte))0x15c83f310;
  }
  namespace Network {
    static undefined8(*DmgPacket_)() = (undefined8(*)())0x15cca7800;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x159d4d540;
  }
  namespace QuestBoard {
    static undefined8(*DisplayQuests)() = (undefined8(*)())0x15955d8e0;
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x159561750;
  }
}
