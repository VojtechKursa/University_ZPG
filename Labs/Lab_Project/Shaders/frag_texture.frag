#version 400

in vec2 uvCoord;

uniform sampler2D textureUnitId;

uniform vec3 highlightColor = vec3(0,0,0);

out vec4 fragColor;

void main (void)
{
    fragColor = texture(textureUnitId, uvCoord) + vec4(highlightColor, 0);
}