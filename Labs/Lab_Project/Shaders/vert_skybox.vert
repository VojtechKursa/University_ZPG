#version 330

layout(location=0) in vec3 pos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 localPos;

void main () {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);

	localPos = pos;
}