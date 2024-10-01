#pragma once

#ifdef RHI_EXPORTS
#	define RHI_API __declspec(dllexport)
#else
#	define RHI_API __declspec(dllimport)
#endif

#include <iostream>

namespace RHI {
	RHI_API int createWindow(int Width, int Height, const char* WindowTitle);
}
