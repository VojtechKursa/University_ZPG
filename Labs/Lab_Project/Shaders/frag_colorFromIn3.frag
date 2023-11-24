#version 330

in vec3 color;

uniform vec3 highlightColor = vec3(0,0,0);

out vec4 frag_colour;

void main () {
	frag_colour = vec4(color + highlightColor, 1.0);
}