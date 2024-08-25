#pragma once

/* Error Detection facilities */

namespace Utils {

	std::string readShaderSource(const char* filePath);

	void printShaderLog(GLuint shader);

	void printProgramLog(int program);

	bool checkOpenGLError();

}