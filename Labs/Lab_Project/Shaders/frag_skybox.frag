#version 400

in vec3 localPos;

uniform samplerCube textureUnitId;

out vec4 fragColor;

void main (void)
{
    fragColor = texture(textureUnitId, localPos);
}