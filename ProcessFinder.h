#pragma once

#include "Libraries.h"

const char* processName = "thedivision.exe";

class ProcessFinder
{
public:
	DWORD SearchProcess(const char* processName)
	{
		DWORD processId = 0;

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hSnapshot != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32 processEntry;
			processEntry.dwSize = sizeof(PROCESSENTRY32);

			if (Process32First(hSnapshot, &processEntry))
			{
				do
				{
					if (_stricmp(processEntry.szExeFile, processName) == 0)
					{
						processId = processEntry.th32ProcessID;
						break;
					}
				} while (Process32Next(hSnapshot, &processEntry));
			}

			CloseHandle(hSnapshot);
		}

		return processId;
	}

	bool isProcessFound()
	{
		if (!SearchProcess(processName))
		{
			return false;
		}

		return true;
	}
};

