#version 400

uniform vec3 objColor;

out vec4 fragColor;

void main (void)
{
    fragColor = vec4(objColor, 1.0);
}