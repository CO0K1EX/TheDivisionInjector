#pragma once
#include "Libraries.h"

class Inject
{
public:
	BOOL InjectDLL(DWORD ProcId, const char* dllpath)
	{
		BOOL WPM = 0;

		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcId);
		if (hProc == INVALID_HANDLE_VALUE)
		{
			return -1;
		}
		void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		WPM = WriteProcessMemory(hProc, loc, dllpath, strlen(dllpath) + 1, 0);
		if (!WPM)
		{
			CloseHandle(hProc);
			return -1;
		}

		HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
		if (!hThread)
		{
			VirtualFree(loc, strlen(dllpath) + 1, MEM_RELEASE);
			CloseHandle(hProc);
			return -1;
		}

		CloseHandle(hProc);
		VirtualFree(loc, strlen(dllpath) + 1, MEM_RELEASE);
		CloseHandle(hThread);
		return 0;
	}
};

