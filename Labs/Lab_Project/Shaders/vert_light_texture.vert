#version 330

layout(location=0) in vec3 pos;
layout(location=1) in vec3 norm;
layout(location=2) in vec2 uv; 

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec4 worldPos;
out vec3 worldNor;
out vec2 uvCoord;

void main () {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);

    worldPos = modelMatrix * vec4(pos, 1.0);
	worldNor = normalMatrix * norm;
	uvCoord = uv;
}