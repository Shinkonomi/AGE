#include <iostream>
#include <fstream>
#include <string>

#include <ARE.h>

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
	// First call to the render engine
	int returnedValueFromARE = ARECreateWindow(1280, 720, "All Star Render Engine - Test Window", 0);
	if (returnedValueFromARE > 0)
		exit(returnedValueFromARE);

	std::vector<AREShaderProgram*> Programs;
	AREShaderProgram* ShaderProgram = (AREShaderProgram*)malloc(sizeof(AREShaderProgram));
	Programs.push_back(ShaderProgram);
	std::string vertexShaderSource = readShaderSource("shaders\\vertexShader.glsl");
	std::string fragmentShaderSource = readShaderSource("shaders\\fragmentShader.glsl");
	AREInit(Programs, vertexShaderSource, fragmentShaderSource);
	AREBeginRenderLoop(Programs);

	AREDestroyCurrentContext();
	exit(returnedValueFromARE);
}
