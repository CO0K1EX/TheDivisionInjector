#pragma once

#include "Libraries.h"

class WindowLock
{
public:
	void WindowSizeLock()
	{
		HWND console = GetConsoleWindow();

		LONG style = GetWindowLong(console, GWL_STYLE);

		style &= ~WS_SIZEBOX;
		SetWindowLong(console, GWL_STYLE, style);
		SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX);
	}
};

