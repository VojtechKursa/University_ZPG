#version 400

in vec2 uvCoord;

uniform sampler2D textureUnitId;

out vec4 fragColor;

void main (void)
{
    fragColor = texture(textureUnitId, uvCoord);
}