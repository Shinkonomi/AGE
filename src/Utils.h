#pragma once

/* Error Detection facilities */

namespace Utils {

	int  randomNumberGenInRange(int min, int max);

	void printShaderLog(GLuint shader);

	void printProgramLog(int program);

	bool checkOpenGLError();

}