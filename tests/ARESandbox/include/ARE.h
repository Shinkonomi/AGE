#pragma once

#ifdef ARE_EXPORTS
#	define ARE_API __declspec(dllexport)
#else
#	define ARE_API __declspec(dllimport)
#endif

#include <vector>

struct AREShaderProgram {
	unsigned int Program;
};


ARE_API int ARECreateWindow(int windowWidth, int windowHeight, const char* windowTitle, int swapIntervals);

ARE_API void AREInit(std::vector<AREShaderProgram*> shaderPrograms,
	std::string vertexShaderSource, std::string fragmentShaderSource);

ARE_API void AREBeginRenderLoop(std::vector<AREShaderProgram*> shaderPrograms);

ARE_API void AREDestroyCurrentContext();