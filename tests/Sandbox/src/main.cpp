#include <iostream>
#include <fstream>
#include <string>

#include "RHI.h"

std::string readShaderSource(const char* filePath) {
		std::string content;
		std::ifstream fileStream(filePath, std::ios::in);
		std::string line = "";

		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;
	}

int main(void) {
	// First call to the RHI
	int returnedValueFromRHI = RHI::createWindow(1280, 720, "All Star Game Engine - Test Window");
	if (returnedValueFromRHI > 0)
		exit(returnedValueFromRHI);

	std::string vertexShaderSource = readShaderSource("shaders\\vertexShader.glsl");
	std::string fragmentShaderSource = readShaderSource("shaders\\fragmentShader.glsl");

	exit(returnedValueFromRHI);
}
