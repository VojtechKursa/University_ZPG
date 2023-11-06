#version 330

layout(location=0) in vec3 pos;
layout(location=2) in vec2 uv; 

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 uvCoord;

void main () {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
	uvCoord = uv;
}