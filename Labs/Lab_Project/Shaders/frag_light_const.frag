#version 400

in vec4 worldPos;
in vec3 worldNor;

uniform float ambientCoeficient = 1;

uniform vec3 highlightColor = vec3(0,0,0);

uniform vec4 objColor = vec4(0.385, 0.647, 0.812, 1.0);

out vec4 fragColor;

void main (void)
{
    vec4 ambient = vec4(0.5, 0.5, 0.5, 1.0) * ambientCoeficient;

    fragColor = ambient * objColor + vec4(highlightColor, 0);
}