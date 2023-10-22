#version 330

layout(location=0) in vec3 pos;
layout(location=1) in vec3 norm;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 color;

void main () {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
	color = vec4(norm, 1.0);
}