#version 400

layout(location=0) in vec3 pos;
layout(location=1) in vec3 norm;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec4 worldPos;
out vec3 worldNor;

void main (void) {
    worldPos = modelMatrix * vec4(pos, 1.0);
	worldNor = normalMatrix * norm;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
}