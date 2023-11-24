#version 330

in vec3 color;

uniform vec3 highlightColor = vec3(0,0,0);

out vec4 frag_colour;

void main () {
	float val = ((color.x + color.y + color.z) / 3);

	frag_colour = vec4(val + highlightColor.x, val + highlightColor.y, val + highlightColor.z, 1.0);
}