#include <iostream>

#include "ARE.h"

int main(void) {

	// First call to the render engine
	int returnedValueFromARE = AREInit(1920, 1080, "All Star Render Engine - Test Window", 1);

	exit(returnedValueFromARE);
}