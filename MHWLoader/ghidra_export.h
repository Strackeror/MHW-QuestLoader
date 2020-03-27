
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
    static bool(*CanClawTurn)(longlong) = (bool(*)(longlong))0x15dba4570;
    namespace EmDmg {
      static undefined *(*At)(undefined *,uint) = (undefined *(*)(undefined *,uint))0x14785fde0;
      static ulonglong(*Count)(undefined *) = (ulonglong(*)(undefined *))0x146f6b5a0;
    }
    static undefined *(*GetEmDmg)(undefined *) = (undefined *(*)(undefined *))0x15db97bf0;
    static bool(*HasEmDmg)(undefined *) = (bool(*)(undefined *))0x15dbaa320;
    namespace SoftenBuildUp {
      static bool(*AddBuildup)(undefined8,undefined8,float) = (bool(*)(undefined8,undefined8,float))0x146fdefc0;
    }
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x15a1e9af0;
    }
    static bool(*LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x15dbc9cd0;
    static longlong(*MotionFromId)(longlong,ulonglong) = (longlong(*)(longlong,ulonglong))0x15d8ae730;
    static undefined *(*ctor)(undefined *,undefined4,undefined4) = (undefined *(*)(undefined *,undefined4,undefined4))0x15db51800;
    namespace Hitzones {
      static undefined8(*SoftenCalc)() = (undefined8(*)())0x156a19f90;
    }
    static undefined8(*GetHitzoneArray)() = (undefined8(*)())0x15db99f10;
    namespace Unkn {
      static undefined8(*ManageEnrageTimer)() = (undefined8(*)())0x156e2d9b0;
    }
    namespace HealthManager {
      static bool(*DealDamage)(byte *,undefined4,bool) = (bool(*)(byte *,undefined4,bool))0x159a857e0;
    }
    namespace SoftenTimers {
      static bool(*IsPartSoftened)(undefined *,uint,uint) = (bool(*)(undefined *,uint,uint))0x156e2d550;
      namespace Network {
        static undefined8(*WoundNotification)() = (undefined8(*)())0x156e2dea0;
      }
      static undefined *(*WoundPart)(undefined *,uint,float) = (undefined *(*)(undefined *,uint,float))0x156e2e5d0;
      static undefined *(*AddWoundTimer)(undefined *,int,float) = (undefined *(*)(undefined *,int,float))0x156e2e1b0;
      static undefined8(*WoundPartLocal)() = (undefined8(*)())0x140a21410;
    }
    static void(*dtor)(undefined *) = (void(*)(undefined *))0x15db56230;
    namespace Construct {
      static longlong(*ConstructId)(undefined8,uint,uint) = (longlong(*)(undefined8,uint,uint))0x15d57e230;
      static undefined *(*GetConstructorFromId)(uint) = (undefined *(*)(uint))0x15a210990;
      static void *ConstructorArray = (void*)0x143dbf240;
      static undefined8(*ConstructId2)(undefined8,uint,uint,uint) = (undefined8(*)(undefined8,uint,uint,uint))0x15d57fa00;
      static undefined *(*GetConstructorFromId2)(uint) = (undefined *(*)(uint))0x15a211620;
      static void *ConstructorArray2 = (void*)0x143dbf600;
      static undefined8(*CreateFilePaths)() = (undefined8(*)())0x15dbe8270;
    }
  }
  namespace Damage {
    static bool(*FetchReactedAction)(undefined *,uint,uint,uint *) = (bool(*)(undefined *,uint,uint,uint *))0x146f82120;
    static ulonglong(*GetHitzoneValue)(longlong,uint,ulonglong,ulonglong,uint,bool) = (ulonglong(*)(longlong,uint,ulonglong,ulonglong,uint,bool))0x146f87d60;
    static undefined8(*Handling)() = (undefined8(*)())0x146f906b0;
    static undefined8(*CalculateDamage)(undefined,undefined,undefined,undefined,undefined4,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined4,undefined8))0x146f7ebb0;
    static void(*Apply)(undefined *,undefined *,undefined *) = (void(*)(undefined *,undefined *,undefined *))0x146f96010;
    static void(*LoadBaseVals)(undefined *,undefined *,undefined *) = (void(*)(undefined *,undefined *,undefined *))0x146f8a940;
    namespace Unkn {
      static undefined8(*HandleReactionUU)() = (undefined8(*)())0x15d77d440;
      static undefined8(*HandleReactionU)() = (undefined8(*)())0x146f97b20;
    }
    static undefined8(*OverrideReaction)() = (undefined8(*)())0x146f828f0;
    static bool(*ApplySoftenBuildup)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x146f976b0;
  }
  namespace Savefile {
    static bool(*CheckFlag)(longlong,uint) = (bool(*)(longlong,uint))0x15a0b7b40;
  }
  namespace EmSetter {
    static undefined8(*CreateMonster)() = (undefined8(*)())0x15d2bc420;
  }
  namespace File {
    static undefined8(*NativePCCheck)(undefined,undefined,undefined,undefined,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined8))0x15f265f80;
    static undefined8(*FilePathCheck)() = (undefined8(*)())0x15eea1ee0;
    static undefined8(*LoadResource)() = (undefined8(*)())0x15f25b410;
  }
  namespace GameVersion {
    static undefined8(*CalcNum)() = (undefined8(*)())0x15ca15b60;
    static void *StringPtr = (void*)0x143dba7d0;
    static void *String = (void*)0x143133868;
  }
  namespace String {
    static undefined8(*Format__)() = (undefined8(*)())0x147865900;
    namespace Unkn {
      static undefined8(*Unkn)() = (undefined8(*)())0x15f2ad560;
      static undefined8(*Load_)() = (undefined8(*)())0x15ee8b860;
    }
    static undefined8(*Format)(char *,char *) = (undefined8(*)(char *,char *))0x1471563e0;
  }
  namespace Timer {
    static void(*Increase)(longlong) = (void(*)(longlong))0x156e3cec0;
    static bool(*IncreaseTimer)(undefined *,float) = (bool(*)(undefined *,float))0x15a052a80;
  }
  namespace SOBJ {
    static undefined8(*LoadSOBJs)() = (undefined8(*)())0x15d6a40c0;
    namespace Unkn {
      static undefined8(*CalledForEachSobj_)() = (undefined8(*)())0x159fd5fe0;
    }
    static undefined8(*Load)() = (undefined8(*)())0x15eca4730;
    static undefined8(*Spawn)() = (undefined8(*)())0x15eca7690;
  }
  namespace Quest {
    static undefined8(*OptionalCount)() = (undefined8(*)())0x15a0a86b0;
    static void *OptionalIdList = (void*)0x143136680;
    namespace Unkn {
      static bool(*Category0or7)(undefined8) = (bool(*)(undefined8))0x15cccc730;
    }
    static undefined8(*GetCategory)() = (undefined8(*)())0x15cdd3a30;
    static undefined8(*ErrorCheck_)() = (undefined8(*)())0x1597fcf00;
    static undefined8(*ErrorCheck)() = (undefined8(*)())0x1597fd1e0;
    static bool(*CheckProgress)(longlong,int) = (bool(*)(longlong,int))0x15a085d50;
    static bool(*CheckComplete)(longlong,int) = (bool(*)(longlong,int))0x15a085c20;
    static uint(*OptionalAt)(undefined *,int) = (uint(*)(undefined *,int))0x15a0a84d0;
    static void *GlobalOptionalQuestList = (void*)0x144ecacf0;
    static ulonglong(*UnknFilterFlag)(ulonglong,uint,undefined8,undefined8) = (ulonglong(*)(ulonglong,uint,undefined8,undefined8))0x15cdd5d80;
    static bool(*StarCategoryCheck)(undefined8,undefined8,undefined8,undefined8) = (bool(*)(undefined8,undefined8,undefined8,undefined8))0x15902de00;
    namespace QuestData {
      static void *ResourcePtr = (void*)0x144ec2d48;
    }
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144b78bb0;
    }
  }
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x146d35730;
  }
  namespace Network {
    static undefined8(*DmgPacket_)() = (undefined8(*)())0x15d77ee90;
  }
  namespace Chat {
    static void(*BuildShowGameMessage)(undefined8,uint,byte,uint) = (void(*)(undefined8,uint,byte,uint))0x15cf30e20;
    static void *MainPtr = (void*)0x144ec4670;
    static void(*ShowGameMessage)(undefined *,char *,float,uint,byte) = (void(*)(undefined *,char *,float,uint,byte))0x15d261220;
  }
  namespace QuestBoard {
    static undefined8(*DisplayQuests)() = (undefined8(*)())0x15980c7d0;
    static undefined8(*FilterQuestList)() = (undefined8(*)())0x159810bc0;
  }
}
