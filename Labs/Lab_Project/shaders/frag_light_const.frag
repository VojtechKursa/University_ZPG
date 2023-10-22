#version 400

in vec4 worldPos;
in vec3 worldNor;

out vec4 fragColor;

void main (void)
{
    vec4 objColor = vec4(0.385, 0.647, 0.812, 1.0);
    
    vec4 ambient = vec4(0.5, 0.5, 0.5, 1.0);

    fragColor = ambient * objColor;
}