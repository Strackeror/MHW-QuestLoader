// MinimalDInput8Hook.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DInput8.h"
DirectInput8Create_t OriginalFunction = nullptr;
HMODULE DInput8DLL = nullptr;



DINPUT8_API HRESULT DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter)
{
	if (OriginalFunction)
	{
		return OriginalFunction(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	}
	return S_FALSE;
}
