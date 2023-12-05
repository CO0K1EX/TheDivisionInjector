#include "Libraries.h"

#include "ProcessFinder.h"
#include "Inject.h"
#include "WindowLock.h"


int main()
{
	SetConsoleTitleW(L"DivisionInjector");

	system("cls");

	ProcessFinder objProcessFinder;
	Inject objInject;
	WindowLock objWindowLock;


	if (!objProcessFinder.isProcessFound())
	{
		std::cout << "Process: " << dye::red_on_black("Not found");
		Sleep(1000);
		main();
	}
	else
	{
		std::cout << "Process: " << dye::green_on_black("Found");
		Sleep(2000);
	}

	system("cls");

	std::cout << dye::yellow_on_black("DLL injector for The Division | version 1.0.0\n");
	std::cout << "\nCreator by CO0K1E\n\n";

	std::string dllPath, procId;
	std::cout << "DLL path: ";
	std::cin >> dllPath;

	DWORD processGame = 0;

	processGame = objProcessFinder.SearchProcess(processName);

	if (PathFileExistsA(dllPath.c_str()) == FALSE)
	{
		MessageBoxExW(NULL, L"DLL file does not exist!", L"Oh uh", MB_OK | MB_ICONERROR, LANG_ENGLISH);
		return EXIT_FAILURE;
	}
	else
	{
		objInject.InjectDLL(processGame, dllPath.c_str());

		if (processGame == NULL)
		{
			MessageBoxExW(NULL, L"Failed to inject the game", L"Oh uh", MB_OK | MB_ICONERROR, LANG_ENGLISH);
			return EXIT_FAILURE;
		}
		else
		{
			MessageBoxExW(NULL, L"Success, game injected", NULL, MB_OK | MB_ICONINFORMATION, LANG_ENGLISH);
			return EXIT_SUCCESS;
		}
	}
}