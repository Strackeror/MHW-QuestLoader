#include <windows.h>
#include <stdio.h>
HINSTANCE mHinst = 0, mHinstDLL = 0;
extern "C" UINT_PTR mProcs[44] = { 0 };

LPCSTR mImportNames[] = { "HidD_FlushQueue", "HidD_FreePreparsedData", "HidD_GetAttributes", "HidD_GetConfiguration", "HidD_GetFeature", "HidD_GetHidGuid", "HidD_GetIndexedString", "HidD_GetInputReport", "HidD_GetManufacturerString", "HidD_GetMsGenreDescriptor", "HidD_GetNumInputBuffers", "HidD_GetPhysicalDescriptor", "HidD_GetPreparsedData", "HidD_GetProductString", "HidD_GetSerialNumberString", "HidD_Hello", "HidD_SetConfiguration", "HidD_SetFeature", "HidD_SetNumInputBuffers", "HidD_SetOutputReport", "HidP_GetButtonCaps", "HidP_GetCaps", "HidP_GetData", "HidP_GetExtendedAttributes", "HidP_GetLinkCollectionNodes", "HidP_GetScaledUsageValue", "HidP_GetSpecificButtonCaps", "HidP_GetSpecificValueCaps", "HidP_GetUsageValue", "HidP_GetUsageValueArray", "HidP_GetUsages", "HidP_GetUsagesEx", "HidP_GetValueCaps", "HidP_InitializeReportForID", "HidP_MaxDataListLength", "HidP_MaxUsageListLength", "HidP_SetData", "HidP_SetScaledUsageValue", "HidP_SetUsageValue", "HidP_SetUsageValueArray", "HidP_SetUsages", "HidP_TranslateUsagesToI8042ScanCodes", "HidP_UnsetUsages", "HidP_UsageListDifference" };
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	mHinst = hinstDLL;
	if (fdwReason == DLL_PROCESS_ATTACH) {
		mHinstDLL = LoadLibrary("C:\\Windows\\System32\\hid.dll");
		if (!mHinstDLL)
			return (FALSE);
		for (int i = 0; i < 44; i++)
			mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);
        ((char*)0x15e36e180)[0x68] = 0xEB;
	}
	else if (fdwReason == DLL_PROCESS_DETACH) {
		FreeLibrary(mHinstDLL);
	}
	return (FALSE);
}

extern "C" void HidD_FlushQueue_wrapper();
extern "C" void HidD_FreePreparsedData_wrapper();
extern "C" void HidD_GetAttributes_wrapper();
extern "C" void HidD_GetConfiguration_wrapper();
extern "C" void HidD_GetFeature_wrapper();
extern "C" void HidD_GetHidGuid_wrapper();
extern "C" void HidD_GetIndexedString_wrapper();
extern "C" void HidD_GetInputReport_wrapper();
extern "C" void HidD_GetManufacturerString_wrapper();
extern "C" void HidD_GetMsGenreDescriptor_wrapper();
extern "C" void HidD_GetNumInputBuffers_wrapper();
extern "C" void HidD_GetPhysicalDescriptor_wrapper();
extern "C" void HidD_GetPreparsedData_wrapper();
extern "C" void HidD_GetProductString_wrapper();
extern "C" void HidD_GetSerialNumberString_wrapper();
extern "C" void HidD_Hello_wrapper();
extern "C" void HidD_SetConfiguration_wrapper();
extern "C" void HidD_SetFeature_wrapper();
extern "C" void HidD_SetNumInputBuffers_wrapper();
extern "C" void HidD_SetOutputReport_wrapper();
extern "C" void HidP_GetButtonCaps_wrapper();
extern "C" void HidP_GetCaps_wrapper();
extern "C" void HidP_GetData_wrapper();
extern "C" void HidP_GetExtendedAttributes_wrapper();
extern "C" void HidP_GetLinkCollectionNodes_wrapper();
extern "C" void HidP_GetScaledUsageValue_wrapper();
extern "C" void HidP_GetSpecificButtonCaps_wrapper();
extern "C" void HidP_GetSpecificValueCaps_wrapper();
extern "C" void HidP_GetUsageValue_wrapper();
extern "C" void HidP_GetUsageValueArray_wrapper();
extern "C" void HidP_GetUsages_wrapper();
extern "C" void HidP_GetUsagesEx_wrapper();
extern "C" void HidP_GetValueCaps_wrapper();
extern "C" void HidP_InitializeReportForID_wrapper();
extern "C" void HidP_MaxDataListLength_wrapper();
extern "C" void HidP_MaxUsageListLength_wrapper();
extern "C" void HidP_SetData_wrapper();
extern "C" void HidP_SetScaledUsageValue_wrapper();
extern "C" void HidP_SetUsageValue_wrapper();
extern "C" void HidP_SetUsageValueArray_wrapper();
extern "C" void HidP_SetUsages_wrapper();
extern "C" void HidP_TranslateUsagesToI8042ScanCodes_wrapper();
extern "C" void HidP_UnsetUsages_wrapper();
extern "C" void HidP_UsageListDifference_wrapper();
