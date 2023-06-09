#include "includes.h"


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

void WindowSizeLock()
{
	HWND console = GetConsoleWindow();

	LONG style = GetWindowLong(console, GWL_STYLE);

	style &= ~WS_SIZEBOX;
	SetWindowLong(console, GWL_STYLE, style);
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}

bool IsAdmin()
{
	BOOL isAdmin = FALSE;
	PSID adminSid = NULL;
	SID_IDENTIFIER_AUTHORITY ntAuth = SECURITY_NT_AUTHORITY;

	if (AllocateAndInitializeSid(&ntAuth, 2, SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminSid))
	{
		if (!CheckTokenMembership(NULL, adminSid, &isAdmin))
		{
			isAdmin = FALSE;
		}

		FreeSid(adminSid);
	}

	return isAdmin;
}


int main()
{
	SetConsoleTitleW(L"DivisionInjector");

	system("cls");

	WindowSizeLock();

	if (!IsAdmin())
	{
		MessageBoxExW(NULL, L"Run the program as administrator!", L"RIGHTS_ADMINISTRATOR_FAILED", MB_OK | MB_ICONEXCLAMATION, LANG_ENGLISH);
		std::cout << "[MESSAGE] Run the program as administrator and try again!\n\n";
		system("pause");
		return EXIT_FAILURE;
	}

	HANDLE hMutex = CreateMutex(NULL, TRUE, _T("DivisionInjector"));

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBoxExW(NULL, L"The injector is already launched!", L"APP_LAUNCH", MB_OK | MB_ICONSTOP, LANG_ENGLISH);
		std::cout << "[MESSAGE] The injector is already launched!\n";
		CloseHandle(hMutex);
		system("pause");
		return EXIT_FAILURE;
	}

	const char* processName = "thedivision.exe";

	if (!SearchProcess(processName))
	{
		std::cout << "Process: " << dye::red_on_black("Not found ");
		Sleep(7000);
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "Process: " << dye::green_on_black("Found ");
		Sleep(2000);
		system("cls");

		std::cout << dye::yellow_on_black("DLL injector for The Division | version 1.0.0\n");
		std::cout << "\nCreator by CO0K1E\n\n";

		std::string dllPath, procId;
		std::cout << "DLL path: ";
		std::cin >> dllPath;

		DWORD processGame = 0;

		processGame = SearchProcess(processName);

		if (PathFileExistsA(dllPath.c_str()) == FALSE)
		{
			MessageBoxExW(NULL, L"DLL file does not exist!", L"DLL_FILE_NOT_FOUND", MB_OK | MB_ICONERROR, LANG_ENGLISH);
			std::cout << "\n[MESSAGE] DLL file does not exist!\n\n";
			system("pause");
			return EXIT_FAILURE;
		}
		else
		{
			InjectDLL(processGame, dllPath.c_str());

			if (processGame == NULL)
			{
				MessageBoxExW(NULL, L"Failed to inject the game, please try again!", L"FAILED_INJECT_GAME", MB_OK | MB_ICONERROR, LANG_ENGLISH);
				std::cout << "\n[MESSAGE] Failed to inject the game, please try again!\n\n";
				std::cout << GetLastError();
				system("pause");
				return EXIT_FAILURE;
			}
			else
			{
				MessageBoxExW(NULL, L"Success, game injected!", L"SUCCESS_INJECT_GAME", MB_OK | MB_ICONINFORMATION, LANG_ENGLISH);
				printf("\n[MESSAGE] Success, game injected!\n\n");
				system("pause");
				return EXIT_SUCCESS;
			}
		}
	}
}
