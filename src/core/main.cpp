#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ARE.h"
#include "..\GLErrorDetection.h"

GLFWwindow* _window;

GLuint _renderingProgram;
GLuint vao[1];

std::string vertexShaderSource;
std::string fragmentShaderSource;

inline static std::string _readShaderSource(const char* filePath) {
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

static GLuint _createShaderProgram() {
	GLint VSCompiled;
	GLint FSCompiled;
	GLint linked;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char *vsSource = vertexShaderSource.c_str();
	const char *fsSource = fragmentShaderSource.c_str();

	std::cout << "In _createShaderProgram" << std::endl;
	std::cout << vsSource;
	std::cout << fsSource;
	
	std::cout << "Compiling Shaders..." << std::endl;
	glShaderSource(vertexShader, 1, &vsSource, NULL);
	glShaderSource(fragmentShader, 1, &fsSource, NULL);

	glCompileShader(vertexShader);
	checkOpenGLError();
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &VSCompiled);
	if (VSCompiled != 1) {
		std::cout << "Vertex Shader Compilation Failed!" << std::endl;
		printShaderLog(vertexShader);
	}

	glCompileShader(fragmentShader);
	checkOpenGLError();
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &FSCompiled);
	if (FSCompiled != 1) {
		std::cout << "Fragment Shader Compilation Failed!" << std::endl;
		printShaderLog(fragmentShader);
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	checkOpenGLError();
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		std::cout << "Linking The Shader Program Failed!" << std::endl;
		printProgramLog(shaderProgram);
	}

	std::cout << "Shaders are successfully compiled" << std::endl;

	return shaderProgram;
}

void _init(GLFWwindow* window) {
	_renderingProgram = _createShaderProgram();
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
}

void _display(GLFWwindow* window, double currentTime) {
	glUseProgram(_renderingProgram);
	glPointSize(100.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
	vertexShaderSource = _readShaderSource(vsFilePath);
	fragmentShaderSource = _readShaderSource(fsFilePath);

	std::cout << "In AREInit" << std::endl;
	std::cout << vertexShaderSource;
	std::cout << fragmentShaderSource;

	_init(_window);

	while (!glfwWindowShouldClose(_window)) {
		_display(_window, glfwGetTime());
		//printf("%d\n", glfwGetTime());
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	// Clean Up
	glfwDestroyWindow(_window);
	glfwTerminate();
}