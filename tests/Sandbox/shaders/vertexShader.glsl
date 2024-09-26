#version 460
layout (location = 0) in vec3 aPos;

uniform float offset;
void main(void) {
	if (gl_VertexID == 0)
		gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
	else if (gl_VertexID == 1)
		gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
	else
		gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);
}