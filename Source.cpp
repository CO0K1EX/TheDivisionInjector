#include <iostream>
#include <Windows.h>

#include "ProcessFinder.h"
#include "Inject.h"
#include "Console.h"

ProcessFinder procFinder;
Inject inject;
Console console;

DWORD dwProcessName = 0;

void ProcessStatus()
{
	while (!procFinder.isProcessFound())
	{
		std::cout << "\rProcess: " << "\033[31mNot found\033[0m" << std::flush;
		Sleep(2000);
	}

	std::cout << "\r\033[2K";
	std::cout << "Process: " << "\033[32mFound\033[0m" << std::flush;
	Sleep(2000);
}

int main()
{
	SetConsoleTitleA("DivisionInjector v1.5");
	
	console.ConsoleSizeLock();

	console.EnableANSI();

	std::cout << "\033[33m   ___  _      _     _           ____       _         __          \033[0m\n";
	std::cout << "\033[33m  / _ \\(_)  __(_)__ (_)__  ___  /  _/__    (_)__ ____/ /____  ____\033[0m\n";
	std::cout << "\033[33m / // / / |/ / (_-</ / _ \\/ _ \\_/ // _ \\  / / -_) __/ __/ _ \\/ __/\033[0m\n";
	std::cout << "\033[33m/____/_/|___/_/___/_/\\___/_//_/___/_//_/_/ /\\__/\\__/\\__/\\___/_/   \033[0m\n";
	std::cout << "\033[33m                                      |___/                       \033[0m\n";

	std::cout << "DLL Injector for The Division | \033[5mMade by CO0K1E\033[0m\n\n";

	ProcessStatus();

	dwProcessName = procFinder.ProcessSearch(procFinder.processName);

	std::cout << "\r\033[2K";

	std::string dllPath;
	std::cout << "DLL path: ";
	std::cin >> dllPath;

	if (!PathFileExistsA(dllPath.c_str()))
	{
		MessageBox(nullptr, "DLL file does not exist.", "Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	if (!inject.InjectDLL(dwProcessName, dllPath.c_str()))
	{
		MessageBox(nullptr, "Success, game injected.", "", MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(nullptr, "Failed to inject the game", "Error", MB_OK | MB_ICONERROR);
		return 1;
	}

	return 0;
}