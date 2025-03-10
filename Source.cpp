#include "Libraries.h"

#include "ProcessFinder.h"
#include "Inject.h"
#include "WindowLock.h"

ProcessFinder objProcessFinder;
Inject objInject;
WindowLock objWindowLock;

DWORD process_name_dw = 0;

void processStatus()
{
	system("cls");

	if (!objProcessFinder.isProcessFound())
	{
		std::cout << "Process: " << dye::red_on_black("Not found");
		Sleep(2000);
		processStatus();
	}
	else
	{
		std::cout << "Process: " << dye::green_on_black("Found");
		Sleep(2500);
	}
}

int main()
{
	SetConsoleTitleW(L"DivisionInjector");
	
	objWindowLock.WindowSizeLock();

	processStatus();

	process_name_dw = objProcessFinder.SearchProcess(process_name);

	system("cls");

	std::cout << dye::yellow_on_black("DLL injector for The Division | version 1.0.0\n\nCreator by CO0K1E\n\n");
	std::string dllPath;
	std::cout << "DLL path: ";
	std::cin >> dllPath;

	if (!PathFileExistsA(dllPath.c_str()))
	{
		MessageBox(nullptr, "DLL file does not exist!", "Oh uh", MB_OK | MB_ICONERROR);
		return 1;
	}
	
	if (objInject.InjectDLL(process_name_dw, dllPath.c_str()) == 0)
	{
		MessageBox(nullptr, "Success, game injected", "", MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	else
	{
		MessageBox(nullptr, "Failed to inject the game", "Oh uh", MB_OK | MB_ICONERROR);
		return 1;
	}
}
