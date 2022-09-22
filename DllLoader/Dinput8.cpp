#include "DInput8.h"
tDirectInput8Create oDirectInput8Create = nullptr;
HMODULE hMod = nullptr;


HRESULT WINAPI DirectInput8Create(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk)
{
    if (oDirectInput8Create) {
        return oDirectInput8Create(inst_handle, version, r_iid, out_wrapper, p_unk);
    }
    return S_FALSE;
}