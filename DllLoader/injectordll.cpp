
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <string>

#include <windows.h>
#include <stdio.h>

#include "../external/MemoryModule/MemoryModule.h"


#pragma region Proxy
struct hid_dll {
	HMODULE dll;
	FARPROC oHidD_FlushQueue;
	FARPROC oHidD_FreePreparsedData;
	FARPROC oHidD_GetAttributes;
	FARPROC oHidD_GetConfiguration;
	FARPROC oHidD_GetFeature;
	FARPROC oHidD_GetHidGuid;
	FARPROC oHidD_GetIndexedString;
	FARPROC oHidD_GetInputReport;
	FARPROC oHidD_GetManufacturerString;
	FARPROC oHidD_GetMsGenreDescriptor;
	FARPROC oHidD_GetNumInputBuffers;
	FARPROC oHidD_GetPhysicalDescriptor;
	FARPROC oHidD_GetPreparsedData;
	FARPROC oHidD_GetProductString;
	FARPROC oHidD_GetSerialNumberString;
	FARPROC oHidD_Hello;
	FARPROC oHidD_SetConfiguration;
	FARPROC oHidD_SetFeature;
	FARPROC oHidD_SetNumInputBuffers;
	FARPROC oHidD_SetOutputReport;
	FARPROC oHidP_GetButtonCaps;
	FARPROC oHidP_GetCaps;
	FARPROC oHidP_GetData;
	FARPROC oHidP_GetExtendedAttributes;
	FARPROC oHidP_GetLinkCollectionNodes;
	FARPROC oHidP_GetScaledUsageValue;
	FARPROC oHidP_GetSpecificButtonCaps;
	FARPROC oHidP_GetSpecificValueCaps;
	FARPROC oHidP_GetUsageValue;
	FARPROC oHidP_GetUsageValueArray;
	FARPROC oHidP_GetUsages;
	FARPROC oHidP_GetUsagesEx;
	FARPROC oHidP_GetValueCaps;
	FARPROC oHidP_InitializeReportForID;
	FARPROC oHidP_MaxDataListLength;
	FARPROC oHidP_MaxUsageListLength;
	FARPROC oHidP_SetData;
	FARPROC oHidP_SetScaledUsageValue;
	FARPROC oHidP_SetUsageValue;
	FARPROC oHidP_SetUsageValueArray;
	FARPROC oHidP_SetUsages;
	FARPROC oHidP_TranslateUsagesToI8042ScanCodes;
	FARPROC oHidP_UnsetUsages;
	FARPROC oHidP_UsageListDifference;
} hid;

extern "C" {
	FARPROC PA = 0;
	int runASM();

	void fHidD_FlushQueue() { PA = hid.oHidD_FlushQueue; runASM(); }
	void fHidD_FreePreparsedData() { PA = hid.oHidD_FreePreparsedData; runASM(); }
	void fHidD_GetAttributes() { PA = hid.oHidD_GetAttributes; runASM(); }
	void fHidD_GetConfiguration() { PA = hid.oHidD_GetConfiguration; runASM(); }
	void fHidD_GetFeature() { PA = hid.oHidD_GetFeature; runASM(); }
	void fHidD_GetHidGuid() { PA = hid.oHidD_GetHidGuid; runASM(); }
	void fHidD_GetIndexedString() { PA = hid.oHidD_GetIndexedString; runASM(); }
	void fHidD_GetInputReport() { PA = hid.oHidD_GetInputReport; runASM(); }
	void fHidD_GetManufacturerString() { PA = hid.oHidD_GetManufacturerString; runASM(); }
	void fHidD_GetMsGenreDescriptor() { PA = hid.oHidD_GetMsGenreDescriptor; runASM(); }
	void fHidD_GetNumInputBuffers() { PA = hid.oHidD_GetNumInputBuffers; runASM(); }
	void fHidD_GetPhysicalDescriptor() { PA = hid.oHidD_GetPhysicalDescriptor; runASM(); }
	void fHidD_GetPreparsedData() { PA = hid.oHidD_GetPreparsedData; runASM(); }
	void fHidD_GetProductString() { PA = hid.oHidD_GetProductString; runASM(); }
	void fHidD_GetSerialNumberString() { PA = hid.oHidD_GetSerialNumberString; runASM(); }
	void fHidD_Hello() { PA = hid.oHidD_Hello; runASM(); }
	void fHidD_SetConfiguration() { PA = hid.oHidD_SetConfiguration; runASM(); }
	void fHidD_SetFeature() { PA = hid.oHidD_SetFeature; runASM(); }
	void fHidD_SetNumInputBuffers() { PA = hid.oHidD_SetNumInputBuffers; runASM(); }
	void fHidD_SetOutputReport() { PA = hid.oHidD_SetOutputReport; runASM(); }
	void fHidP_GetButtonCaps() { PA = hid.oHidP_GetButtonCaps; runASM(); }
	void fHidP_GetCaps() { PA = hid.oHidP_GetCaps; runASM(); }
	void fHidP_GetData() { PA = hid.oHidP_GetData; runASM(); }
	void fHidP_GetExtendedAttributes() { PA = hid.oHidP_GetExtendedAttributes; runASM(); }
	void fHidP_GetLinkCollectionNodes() { PA = hid.oHidP_GetLinkCollectionNodes; runASM(); }
	void fHidP_GetScaledUsageValue() { PA = hid.oHidP_GetScaledUsageValue; runASM(); }
	void fHidP_GetSpecificButtonCaps() { PA = hid.oHidP_GetSpecificButtonCaps; runASM(); }
	void fHidP_GetSpecificValueCaps() { PA = hid.oHidP_GetSpecificValueCaps; runASM(); }
	void fHidP_GetUsageValue() { PA = hid.oHidP_GetUsageValue; runASM(); }
	void fHidP_GetUsageValueArray() { PA = hid.oHidP_GetUsageValueArray; runASM(); }
	void fHidP_GetUsages() { PA = hid.oHidP_GetUsages; runASM(); }
	void fHidP_GetUsagesEx() { PA = hid.oHidP_GetUsagesEx; runASM(); }
	void fHidP_GetValueCaps() { PA = hid.oHidP_GetValueCaps; runASM(); }
	void fHidP_InitializeReportForID() { PA = hid.oHidP_InitializeReportForID; runASM(); }
	void fHidP_MaxDataListLength() { PA = hid.oHidP_MaxDataListLength; runASM(); }
	void fHidP_MaxUsageListLength() { PA = hid.oHidP_MaxUsageListLength; runASM(); }
	void fHidP_SetData() { PA = hid.oHidP_SetData; runASM(); }
	void fHidP_SetScaledUsageValue() { PA = hid.oHidP_SetScaledUsageValue; runASM(); }
	void fHidP_SetUsageValue() { PA = hid.oHidP_SetUsageValue; runASM(); }
	void fHidP_SetUsageValueArray() { PA = hid.oHidP_SetUsageValueArray; runASM(); }
	void fHidP_SetUsages() { PA = hid.oHidP_SetUsages; runASM(); }
	void fHidP_TranslateUsagesToI8042ScanCodes() { PA = hid.oHidP_TranslateUsagesToI8042ScanCodes; runASM(); }
	void fHidP_UnsetUsages() { PA = hid.oHidP_UnsetUsages; runASM(); }
	void fHidP_UsageListDifference() { PA = hid.oHidP_UsageListDifference; runASM(); }
}

void setupFunctions() {
	hid.oHidD_FlushQueue = GetProcAddress(hid.dll, "HidD_FlushQueue");
	hid.oHidD_FreePreparsedData = GetProcAddress(hid.dll, "HidD_FreePreparsedData");
	hid.oHidD_GetAttributes = GetProcAddress(hid.dll, "HidD_GetAttributes");
	hid.oHidD_GetConfiguration = GetProcAddress(hid.dll, "HidD_GetConfiguration");
	hid.oHidD_GetFeature = GetProcAddress(hid.dll, "HidD_GetFeature");
	hid.oHidD_GetHidGuid = GetProcAddress(hid.dll, "HidD_GetHidGuid");
	hid.oHidD_GetIndexedString = GetProcAddress(hid.dll, "HidD_GetIndexedString");
	hid.oHidD_GetInputReport = GetProcAddress(hid.dll, "HidD_GetInputReport");
	hid.oHidD_GetManufacturerString = GetProcAddress(hid.dll, "HidD_GetManufacturerString");
	hid.oHidD_GetMsGenreDescriptor = GetProcAddress(hid.dll, "HidD_GetMsGenreDescriptor");
	hid.oHidD_GetNumInputBuffers = GetProcAddress(hid.dll, "HidD_GetNumInputBuffers");
	hid.oHidD_GetPhysicalDescriptor = GetProcAddress(hid.dll, "HidD_GetPhysicalDescriptor");
	hid.oHidD_GetPreparsedData = GetProcAddress(hid.dll, "HidD_GetPreparsedData");
	hid.oHidD_GetProductString = GetProcAddress(hid.dll, "HidD_GetProductString");
	hid.oHidD_GetSerialNumberString = GetProcAddress(hid.dll, "HidD_GetSerialNumberString");
	hid.oHidD_Hello = GetProcAddress(hid.dll, "HidD_Hello");
	hid.oHidD_SetConfiguration = GetProcAddress(hid.dll, "HidD_SetConfiguration");
	hid.oHidD_SetFeature = GetProcAddress(hid.dll, "HidD_SetFeature");
	hid.oHidD_SetNumInputBuffers = GetProcAddress(hid.dll, "HidD_SetNumInputBuffers");
	hid.oHidD_SetOutputReport = GetProcAddress(hid.dll, "HidD_SetOutputReport");
	hid.oHidP_GetButtonCaps = GetProcAddress(hid.dll, "HidP_GetButtonCaps");
	hid.oHidP_GetCaps = GetProcAddress(hid.dll, "HidP_GetCaps");
	hid.oHidP_GetData = GetProcAddress(hid.dll, "HidP_GetData");
	hid.oHidP_GetExtendedAttributes = GetProcAddress(hid.dll, "HidP_GetExtendedAttributes");
	hid.oHidP_GetLinkCollectionNodes = GetProcAddress(hid.dll, "HidP_GetLinkCollectionNodes");
	hid.oHidP_GetScaledUsageValue = GetProcAddress(hid.dll, "HidP_GetScaledUsageValue");
	hid.oHidP_GetSpecificButtonCaps = GetProcAddress(hid.dll, "HidP_GetSpecificButtonCaps");
	hid.oHidP_GetSpecificValueCaps = GetProcAddress(hid.dll, "HidP_GetSpecificValueCaps");
	hid.oHidP_GetUsageValue = GetProcAddress(hid.dll, "HidP_GetUsageValue");
	hid.oHidP_GetUsageValueArray = GetProcAddress(hid.dll, "HidP_GetUsageValueArray");
	hid.oHidP_GetUsages = GetProcAddress(hid.dll, "HidP_GetUsages");
	hid.oHidP_GetUsagesEx = GetProcAddress(hid.dll, "HidP_GetUsagesEx");
	hid.oHidP_GetValueCaps = GetProcAddress(hid.dll, "HidP_GetValueCaps");
	hid.oHidP_InitializeReportForID = GetProcAddress(hid.dll, "HidP_InitializeReportForID");
	hid.oHidP_MaxDataListLength = GetProcAddress(hid.dll, "HidP_MaxDataListLength");
	hid.oHidP_MaxUsageListLength = GetProcAddress(hid.dll, "HidP_MaxUsageListLength");
	hid.oHidP_SetData = GetProcAddress(hid.dll, "HidP_SetData");
	hid.oHidP_SetScaledUsageValue = GetProcAddress(hid.dll, "HidP_SetScaledUsageValue");
	hid.oHidP_SetUsageValue = GetProcAddress(hid.dll, "HidP_SetUsageValue");
	hid.oHidP_SetUsageValueArray = GetProcAddress(hid.dll, "HidP_SetUsageValueArray");
	hid.oHidP_SetUsages = GetProcAddress(hid.dll, "HidP_SetUsages");
	hid.oHidP_TranslateUsagesToI8042ScanCodes = GetProcAddress(hid.dll, "HidP_TranslateUsagesToI8042ScanCodes");
	hid.oHidP_UnsetUsages = GetProcAddress(hid.dll, "HidP_UnsetUsages");
	hid.oHidP_UsageListDifference = GetProcAddress(hid.dll, "HidP_UsageListDifference");
}
#pragma endregion

void LoadLoader() 
{
	const char path[] = "loader.dll";
	std::ifstream dll(path, std::ios::binary);
	std::vector<char> dllRead(std::istreambuf_iterator<char>(dll), {});

	size_t size = dllRead.size();
	char* allocatedMem = (char*) malloc(size);
	if (!allocatedMem)
		return;
	memcpy(allocatedMem, &dllRead[0], size);
	auto target = MemoryLoadLibrary(allocatedMem, size);
	typedef void(*initF)(void*);
	((initF)MemoryGetProcAddress(target, "Initialize"))(target);
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		char path[MAX_PATH];
		GetWindowsDirectory(path, sizeof(path));

		strcat_s(path, "\\System32\\hid.dll");
		hid.dll = LoadLibrary(path);
		setupFunctions();

		LoadLoader();

		// Add here your code, I recommend you to create a thread
		break;
	case DLL_PROCESS_DETACH:
		FreeLibrary(hid.dll);
		break;
	}
	return 1;
}

