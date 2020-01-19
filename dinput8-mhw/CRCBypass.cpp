#include <windows.h>
#include <sdkddkver.h>
#include <winternl.h>
#include <tlhelp32.h>

#include <fstream>

#include "log.h"
#include "dll.h"

typedef LONG    NTSTATUS;
typedef NTSTATUS(WINAPI* pNtQIT)(HANDLE, LONG, PVOID, ULONG, PULONG);
#define STATUS_SUCCESS    ((NTSTATUS)0x00000000L)
#define ThreadQuerySetWin32StartAddress 9

DWORD64 GetThreadStartAddress(HANDLE hThread)
{
	NTSTATUS ntStatus;
	HANDLE hDupHandle;
	DWORD64 dwStartAddress;

	pNtQIT NtQueryInformationThread = (pNtQIT)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQueryInformationThread");
	if (NtQueryInformationThread == NULL) return 0;

	HANDLE hCurrentProcess = GetCurrentProcess();
	if (!DuplicateHandle(hCurrentProcess, hThread, hCurrentProcess, &hDupHandle, THREAD_QUERY_INFORMATION, FALSE, 0)) {
		SetLastError(ERROR_ACCESS_DENIED);
		return 0;
	}

	ntStatus = NtQueryInformationThread(hDupHandle, ThreadQuerySetWin32StartAddress, &dwStartAddress, sizeof(DWORD64), NULL);
	CloseHandle(hDupHandle);
	if (ntStatus != STATUS_SUCCESS) return 0;

	return dwStartAddress;
}

void KillCRCThreads()
{
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	auto id = GetCurrentProcessId();
	THREADENTRY32 entry;
	entry.dwSize = sizeof(entry);

	if (!Thread32First(snapshot, &entry))
	{
		LOG(ERR) << "Thread iteration failed";
	}

	do {
		if (entry.th32OwnerProcessID == id)
		{
			auto thread = OpenThread(THREAD_ALL_ACCESS, false, entry.th32ThreadID);
			if (thread != NULL)
			{
				DWORD64 addr = GetThreadStartAddress(thread);
				DWORD64 addr_range[] = { 0x1418c5770 , 0x141906100 };
				if (addr >= addr_range[0] && addr <= addr_range[1] &&
					((addr - addr_range[0]) % 0x2CF0) == 0)
				{
					LOG(WARN) << "Terminated thread : " << std::hex << addr;
					TerminateThread(thread, 0);
				}
				CloseHandle(thread);
			}
		}
	} while (Thread32Next(snapshot, &entry));
}

void CRCBypassDump()
{
	std::ifstream input("EXEDiffOnly_CRC_Bypassed", std::ios::binary);
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

	memcpy((void*)0x143310fe0, &buffer[0], buffer.size());
}


