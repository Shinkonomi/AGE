#pragma once

#ifdef ARE_EXPORTS
#	define ARE_API __declspec(dllexport)
#else
#	define ARE_API __declspec(dllimport)
#endif

#include <vector>

struct ARE_ShaderProgram {
	unsigned int Program;
};

typedef unsigned int ARE_VAO;

typedef unsigned int ARE_VBO;

typedef unsigned int ARE_EBO;


ARE_API int ARECreateWindow(int windowWidth, int windowHeight, const char* windowTitle, int swapIntervals);

ARE_API void AREInit(std::vector<ARE_ShaderProgram*> shaderPrograms,
	std::string vertexShaderSource, std::string fragmentShaderSource);

ARE_API void AREBeginRenderLoop(std::vector<ARE_ShaderProgram*> shaderPrograms);

ARE_API void AREDestroyCurrentContext();