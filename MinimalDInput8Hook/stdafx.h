// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <winternl.h>
#include <imagehlp.h>


#ifdef DLL_EXPORT
#define DINPUT8_API __declspec(dllexport)
#else
#define DINPUT8_API __declspec(dllimport)
#endif

// reference additional headers your program requires here
