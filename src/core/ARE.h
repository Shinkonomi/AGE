#pragma once

#ifdef ARE_EXPORTS
#	define ARE_API __declspec(dllexport)
#else
#	define ARE_API __declspec(dllimport)
#endif

extern "C" {

	ARE_API int AREInit(int windowWidth, int windowHeight, const char* windowTitle, int swapIntervals);

}