#version 330

in vec4 color;

uniform vec3 highlightColor = vec3(0,0,0);

out vec4 frag_colour;

void main () {
	frag_colour = color + vec4(highlightColor, 0.0);
}