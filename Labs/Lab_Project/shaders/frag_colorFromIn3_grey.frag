#version 330

in vec3 color;

out vec4 frag_colour;

void main () {
	float val = ((color.x + color.y + color.z) / 3);

	frag_colour = vec4(val, val, val, 1.0);
}