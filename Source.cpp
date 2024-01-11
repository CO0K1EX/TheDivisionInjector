#include "Libraries.h"

#include "ProcessFinder.h"
#include "Inject.h"
#include "WindowLock.h"

int main()
{
	SetConsoleTitleW(L"DivisionInjector");
	
	ProcessFinder objProcessFinder;
	Inject objInject;
	WindowLock objWindowLock;

	objWindowLock.WindowSizeLock();

	DWORD processGame = 0;

	processGame = objProcessFinder.SearchProcess(processName);

	if (!objProcessFinder.isProcessFound())
	{
		std::cout << "Process: " << dye::red_on_black("Not found");
		Sleep(2500);
		return EXIT_FAILURE;
	}

	std::cout << "Process: " << dye::green_on_black("Found");
	Sleep(2000);

	system("cls");

	std::cout << dye::yellow_on_black("DLL injector for The Division | version 1.0.0\n\nCreator by CO0K1E\n\n");

	std::string dllPath, procId;
	std::cout << "DLL path: ";
	std::cin >> dllPath;

	if (!PathFileExistsA(dllPath.c_str()))
	{
		MessageBox(NULL, "DLL file does not exist!", "Oh uh", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}
	
	if (objInject.InjectDLL(processGame, dllPath.c_str()) == 0)
	{
		MessageBox(0, "Success, game injected", "", MB_OK | MB_ICONINFORMATION);
		return EXIT_SUCCESS;
	}
	else
	{
		MessageBox(0, "Failed to inject the game", "Oh uh", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}
}