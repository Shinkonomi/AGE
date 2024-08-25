#include <iostream>

#include "ARE.h"

int main(void) {

	// First call to the render engine
	int returnedValueFromARE = ARECreateWindow(1280, 720, "All Star Render Engine - Test Window", 1);
	if (returnedValueFromARE)
		exit(returnedValueFromARE);

	AREInit("shaders\\vertexShader.glsl", "shaders\\fragmentShader.glsl");

	exit(returnedValueFromARE);
}