#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <tchar.h>

#pragma comment(lib,"shlwapi.lib")

#define print(format, ...) frprintf (stderr,format, __VA_ARGS__)