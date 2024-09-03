#pragma once

#include <glm/glm.hpp>

typedef glm::mat4 mat4;

namespace Math {

	mat4 buildTranslate(float X, float Y, float Z);

	mat4 buildRotateRoll(float Radian);

	mat4 buildRotatePitch(float Radian);

	mat4 buildRotateYaw(float Radian);

	mat4 buildScale(float X, float Y, float Z);
}