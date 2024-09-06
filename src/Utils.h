#pragma once

/* Error Detection facilities */

namespace Utils {

	int  randomNumberGenInRange(int min, int max);

	std::string readShaderSource(const char* filePath);

	void printShaderLog(GLuint shader);

	void printProgramLog(int program);

	bool checkOpenGLError();

}