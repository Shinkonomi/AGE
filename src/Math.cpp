#include "Math.h"

namespace Math {
	/*
	Important Notice: Matracies are filled starting with the leftmost column 
	*/

	/*Builds and returns a transformation matrix*/
	mat4 buildTranslate(float x, float y, float z) {
		mat4 matrix = mat4(1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 0.0,
			x, y, z, 1.0);
		return matrix;
	}

	/*Builds and returns a matrix that performs a roll rotaion (X axis)*/
	mat4 buildRotateRoll(float radian) {
		mat4 matrix = mat4(1.0, 0.0, 0.0, 0.0,
			0.0, cos(radian), -sin(radian), 0.0,
			0.0, sin(radian), cos(radian), 0.0,
			0.0, 0.0, 0.0, 1.0);
		return matrix;
	}

	/*Builds and returns a matrix that performs a pitch rotation (Y axis)*/
	mat4 buildRotatePitch(float radian) {
		mat4 matrix = mat4(cos(radian), 0.0, sin(radian), 0.0,
			0.0, 1.0, 0.0, 0.0,
			-sin(radian), 0.0, cos(radian), 0.0,
			0.0, 0.0, 0.0, 1.0);
		return matrix;
	}

	/*Builds and returns a matrix that performs a yaw rotaion (Z axis)*/
	mat4 buildRotateYaw(float radian) {
		mat4 matrix = mat4(cos(radian), -sin(radian), 0.0, 0.0,
			sin(radian), cos(radian), 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);
		return matrix;
	}

	/*Builds and returns a scale matrix*/
	mat4 buildScale(float x, float y, float z) {
		mat4 matrix = mat4(x, 0.0, 0.0, 0.0,
			0.0, y, 0.0, 0.0,
			0.0, 0.0, z, 0.0,
			0.0, 0.0, 0.0, 1.0);
		return matrix;
	}
}