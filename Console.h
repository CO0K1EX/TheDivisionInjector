#pragma once

#include "Libraries.h"

class Console
{
public:
	void ConsoleSizeLock(int windowX = 600, int windowY = 200)
	{
		HWND console = GetConsoleWindow();
		RECT r;
		LONG style = GetWindowLong(console, GWL_STYLE);

		GetWindowRect(console, &r);

		MoveWindow(console, r.left, r.top, windowX, windowY, TRUE);

		ShowScrollBar(GetConsoleWindow(), SB_VERT, FALSE);

		style &= ~WS_SIZEBOX;
		SetWindowLong(console, GWL_STYLE, style);
		SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX | WS_VSCROLL);
	}

	void EnableANSI()
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		if (hOut == INVALID_HANDLE_VALUE) return;

		DWORD dwMode = 0;

		if (!GetConsoleMode(hOut, &dwMode)) return;

		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);
	}
};

