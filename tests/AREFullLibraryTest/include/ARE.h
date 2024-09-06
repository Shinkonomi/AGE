#pragma once

#ifdef ARE_EXPORTS
#	define ARE_API __declspec(dllexport)
#else
#	define ARE_API __declspec(dllimport)
#endif

#include <vector>

typedef uint16_t AREShaderProgramIdx;

struct AREShaderProgram {
	AREShaderProgramIdx ShaderProgramIdx;
	uint32_t Program;
};

ARE_API typedef std::vector<AREShaderProgram*> AREShaderPrograms;


ARE_API int ARECreateWindow(int windowWidth, int windowHeight, const char* windowTitle, int swapIntervals);

ARE_API AREShaderPrograms AREInit(const char* vsFilePath, const char* fsFilePath);

ARE_API void AREBeginRenderLoop(AREShaderPrograms shaderPrograms);

ARE_API void AREDestroyCurrentContext();