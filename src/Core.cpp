#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "ARE.h"
#include "Utils.h"

GLFWwindow* _window;

GLuint _renderingProgram;
GLuint vao[1];

std::string vertexShaderSource;
std::string fragmentShaderSource;

static GLuint _createShaderProgram() {
	GLint VSCompiled;
	GLint FSCompiled;
	GLint linked;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char *vsSource = vertexShaderSource.c_str();
	const char *fsSource = fragmentShaderSource.c_str();
	
	std::cout << "Compiling Shaders..." << std::endl;
	glShaderSource(vertexShader, 1, &vsSource, NULL);
	glShaderSource(fragmentShader, 1, &fsSource, NULL);

	glCompileShader(vertexShader);
	Utils::checkOpenGLError();
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &VSCompiled);
	if (VSCompiled != 1) {
		std::cout << "Vertex Shader Compilation Failed!" << std::endl;
		Utils::printShaderLog(vertexShader);
	}

	glCompileShader(fragmentShader);
	Utils::checkOpenGLError();
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &FSCompiled);
	if (FSCompiled != 1) {
		std::cout << "Fragment Shader Compilation Failed!" << std::endl;
		Utils::printShaderLog(fragmentShader);
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	Utils::checkOpenGLError();
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		std::cout << "Linking The Shader Program Failed!" << std::endl;
		Utils::printProgramLog(shaderProgram);
	}

	std::cout << "Shaders are successfully compiled" << std::endl;

	return shaderProgram;
}

void _init(GLFWwindow* window) {
	_renderingProgram = _createShaderProgram();
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
}

float x = 0.0f;
float inc = 0.01f; // Offset
double lastTime = 0;
double deltaTime = 0;

void _display(GLFWwindow* window, double currentTime) {
	deltaTime = currentTime - lastTime;
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.4, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(_renderingProgram);

	x += inc;
	if (x > 1.0f)
		inc = -0.01f;
	if (x < -1.0f)
		inc = 0.01f;
	GLuint offsetLoc = glGetUniformLocation(_renderingProgram, "offset"); // get ptr to "offset"
	glProgramUniform1f(_renderingProgram, offsetLoc, x);

	glPointSize(100.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//std::cout << (1 / deltaTime) << std::endl;
	lastTime = currentTime;
}

int ARECreateWindow(int windowWidth, int windowHeight, const char *windowTitle, int swapIntervals) {
	/* GLFW and GLEW initialization */
	if (!glfwInit()) {
		return EXIT_FAILURE;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	glfwMakeContextCurrent(_window);
	if (glewInit() != GLEW_OK) {
		return EXIT_FAILURE;
	}
	// VSYNC Stuff
	glfwSwapInterval(swapIntervals);

	return EXIT_SUCCESS;
}

void AREInit(const char* vsFilePath, const char* fsFilePath) {
	vertexShaderSource = Utils::readShaderSource(vsFilePath);
	fragmentShaderSource = Utils::readShaderSource(fsFilePath);

	_init(_window);

	while (!glfwWindowShouldClose(_window)) {
		_display(_window, glfwGetTime());
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	// Clean Up
	glfwDestroyWindow(_window);
	glfwTerminate();
}