#pragma once

#include "Libraries.h"

class WindowLock
{
public:
	void WindowSizeLock()
	{
		HWND console = GetConsoleWindow();
		RECT r;
		LONG style = GetWindowLong(console, GWL_STYLE);

		GetWindowRect(console, &r);

		MoveWindow(console, r.left, r.top, 700, 500, TRUE);

		ShowScrollBar(GetConsoleWindow(), SB_VERT, FALSE);

		style &= ~WS_SIZEBOX;
		SetWindowLong(console, GWL_STYLE, style);
		SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX | WS_VSCROLL);
	}
};

