#pragma once

#include "Libraries.h"


class ProcessFinder
{
public:
	DWORD ProcessSearch(const char* process_name)
	{
		DWORD processID = 0;

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hSnapshot != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 processEntry;
			processEntry.dwSize = sizeof(PROCESSENTRY32);

			if (Process32First(hSnapshot, &processEntry))
			{
				do
				{
					if (_stricmp(processEntry.szExeFile, process_name) == 0)
					{
						processID = processEntry.th32ProcessID;
						break;
					}
				} while (Process32Next(hSnapshot, &processEntry));
			}
			CloseHandle(hSnapshot);
		}

		return processID;
	}

	const char* processName = "thedivision.exe";

	bool isProcessFound()
	{
		if (!ProcessSearch(processName))
		{
			return false;
		}

		return true;
	}
};

