#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "ARE.hpp"

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint _createShaderProgram() {
	const char* vertexShaderSource =
		"#version 460 \n"
		"void main(void) {\n"
		"gl_Position = vec4(0.0, 0.0, 0.0, 1.0); \n"
		"}";
	const char* fragmentShaderSource =
		"#version 460 \n"
		"out vec4 color; \n"
		"void main(void) {\n"
		"color = vec4(0.3, 0.0, 1.0, 1.0); \n"
		"}";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	printf("Compiling Shaders...\n");
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	printf("Shaders are successfully compiled.\n");

	return shaderProgram;
}

using namespace std;

void _init(GLFWwindow* window) {
	renderingProgram = _createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

void _display(GLFWwindow* window, double currentTime) {
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);
	glPointSize(30.0f);
	glDrawArrays(GL_POINTS, 0, numVAOs);
}

int AREInit(void) {
	/* GLFW and GLEW initialization */
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "All Star Render Engine - Test Window", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	// VSYNC Stuff
	glfwSwapInterval(1);

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
	exit(EXIT_SUCCESS);
}