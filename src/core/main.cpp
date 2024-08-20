#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "ARE.h"
#include "..\GLErrorDetection.h"

#define numVAOs 1

GLuint _renderingProgram;
GLuint vao[numVAOs];

GLuint _createShaderProgram() {
	GLint VSCompiled;
	GLint FSCompiled;
	GLint linked;

	const char* vertexShaderSource =
		"#version 460 \n"
		"void main(void) {\n"
		"gl_Position = vec4(0.0, 0.0, 0.0, 1.0); \n"
		"}";
	const char* fragmentShaderSource =
		"#version 460 \n"
		"out vec4 color; \n"
		"void main(void) {\n"
		"if (gl_FragCoord.x < 960) color = vec4(0.3, 0.0, 1.0, 1.0); else color = vec4(0.3, 0.0, 0.1, 1.0);\n"
		"}";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	std::cout << "Compiling Shaders..." << std::endl;
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

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
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

void _display(GLFWwindow* window, double currentTime) {
	glUseProgram(_renderingProgram);
	glPointSize(100.0f);
	glDrawArrays(GL_POINTS, 0, numVAOs);
}

int AREInit(int windowWidth, int windowHeight, const char *windowTitle, int swapIntervals) {
	/* GLFW and GLEW initialization */
	if (!glfwInit()) {
		return EXIT_FAILURE;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		return EXIT_FAILURE;
	}
	// VSYNC Stuff
	glfwSwapInterval(swapIntervals);

	_init(window);

	while (!glfwWindowShouldClose(window)) {
		_display(window, glfwGetTime());
		//printf("%d\n", glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean Up
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return EXIT_SUCCESS;
}