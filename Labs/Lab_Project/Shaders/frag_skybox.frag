#version 400

in vec3 localPos;

uniform samplerCube textureUnitId;
uniform float brightness = 1.0;

out vec4 fragColor;

void main (void)
{
    fragColor = texture(textureUnitId, localPos) * brightness;
}