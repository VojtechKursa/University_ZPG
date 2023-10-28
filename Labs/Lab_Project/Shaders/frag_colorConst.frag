#version 400

uniform vec3 objColor3 = vec3(0.385, 0.647, 0.812);

out vec4 fragColor;

void main (void)
{
    fragColor = vec4(objColor3, 1.0);
}