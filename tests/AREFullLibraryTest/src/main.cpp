#include <iostream>

#include <ARE.h>

int main(void) {

	// First call to the render engine
	int returnedValueFromARE = ARECreateWindow(1280, 720, "All Star Render Engine - Test Window", 0);
	if (returnedValueFromARE > 0)
		exit(returnedValueFromARE);

	AREShaderPrograms Programs = AREInit("shaders\\vertexShader.glsl", "shaders\\fragmentShader.glsl");
	AREBeginRenderLoop(Programs);

	AREDestroyCurrentContext();
	exit(returnedValueFromARE);
}