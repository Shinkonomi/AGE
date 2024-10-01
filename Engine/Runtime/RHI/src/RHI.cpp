#define GLFW_INCLUDE_VULKAN

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <windows.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "RHI.h"

namespace RHI {
	int createWindow(int windowWidth, int windowHeight, const char* windowTitle) {
		if (glfwInit() != GLFW_TRUE) {
			std::cerr << "Failed to initialize GLFW" << std::endl;
			return EXIT_FAILURE;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
		if (window == NULL) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			return EXIT_FAILURE;
		}

		uint32_t extentionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, nullptr);
		std::cout << extentionCount << " amount of extentions are supported." << std::endl;

		glm::mat4 matrix = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
		};
		glm::vec4 vector = {
		2.5444, 1.0, 33.34, 1.0
		};
		auto TestMath = matrix * vector;
		std::cout << TestMath.a << "," << TestMath.b << "," << TestMath.g << std::endl;

		Sleep(5000);

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();

		return EXIT_SUCCESS;
	}
}