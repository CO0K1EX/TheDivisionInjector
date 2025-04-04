#pragma once

#include "Libraries.h"

class Inject
{
public:
	BOOL InjectDLL(DWORD procID, const char* dllPath)
	{
		BOOL WPM = 0;

		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procID);

		if (hProc == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}

		void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		
		WPM = WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);

		if (!WPM)
		{
			CloseHandle(hProc);

			return FALSE;
		}

		HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

		if (!hThread)
		{
			VirtualFree(loc, strlen(dllPath) + 1, MEM_RELEASE);
			
			CloseHandle(hProc);
			
			return FALSE;
		}

		CloseHandle(hProc);
		
		VirtualFree(loc, strlen(dllPath) + 1, MEM_RELEASE);
		
		CloseHandle(hThread);
		
		return TRUE;
	}
};

