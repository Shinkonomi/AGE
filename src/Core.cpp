#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <limits>
#include <assert.h>

#include "ARE.h"
#include "Utils.h"
#include "Math.h"

static GLFWwindow* _window;

GLuint vao[1];

std::string _vertexShaderSource;
std::string _fragmentShaderSource;

GLuint _createShaderProgram() {
	GLint VSCompiled;
	GLint FSCompiled;
	GLint linked;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char *vsSource = _vertexShaderSource.c_str();
	const char *fsSource = _fragmentShaderSource.c_str();
	
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

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

GLuint _init(GLFWwindow* window) {
	GLuint renderingProgram = _createShaderProgram();
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	
	return renderingProgram;
}

float x = 0.0f;
float inc = 0.01f; // Offset
double lastTime = 0;
double deltaTime = 0;
double animTickTime = 0.016666667;
double timeSinceLastAnimTick = 0;

void _display(GLFWwindow* window, double currentTime, std::vector<AREShaderProgram*> shaderPrograms) {
	deltaTime = currentTime - lastTime;
	timeSinceLastAnimTick += deltaTime;
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.1, 0.4, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Test
	GLuint renderingProgram = shaderPrograms.at(0)->Program;

	glUseProgram(renderingProgram);

	if (timeSinceLastAnimTick >= animTickTime) {
		x += inc;
		if (x > 1.0f)
			inc = -0.01f;
		if (x < -1.0f)
			inc = 0.01f;
		timeSinceLastAnimTick = 0;
	}
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset"); // get ptr to "offset"
	glProgramUniform1f(renderingProgram, offsetLoc, x);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	std::cout << (1 / deltaTime) << std::endl;
	lastTime = currentTime;
}

void _framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int ARECreateWindow(int windowWidth, int windowHeight, const char *windowTitle, int swapIntervals) {
	/* GLFW and GLEW initialization */
	if (!glfwInit()) {
		return EXIT_FAILURE;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	if (_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		AREDestroyCurrentContext();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(_window);
	if (glewInit() != GLEW_OK) {
		return EXIT_FAILURE;
	}

	glfwSetFramebufferSizeCallback(_window, _framebufferSizeCallback);

	// VSYNC Stuff
	glfwSwapInterval(swapIntervals);

	return EXIT_SUCCESS;
}

void AREInit(std::vector<AREShaderProgram*> shaderPrograms,
	std::string vertexShaderSource, std::string fragmentShaderSource) {
	_vertexShaderSource = vertexShaderSource;
	_fragmentShaderSource = fragmentShaderSource;

	GLuint renderingProgram = _init(_window);
	shaderPrograms.at(0)->Program = renderingProgram;
}

void AREBeginRenderLoop(std::vector<AREShaderProgram*> shaderPrograms) {
	while (!glfwWindowShouldClose(_window)) {
		_display(_window, glfwGetTime(), shaderPrograms);
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void AREDestroyCurrentContext() {
	glfwDestroyWindow(_window);
	glfwTerminate();
}