#version 400

in vec4 worldPos;
in vec3 worldNor;

uniform vec3 lightColor;
uniform vec3 lightPosition;

out vec4 fragColor;

void main (void)
{
    vec4 objColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec4 lightColor4 = vec4(lightColor, 1.0);

    vec3 lightVector = lightPosition - (worldPos.xyz / worldPos.w);

    float dotProduct = max(dot(normalize(lightVector), normalize(worldNor)), 0.0);
    vec4 diffuse = dotProduct * lightColor4;
    
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    fragColor = (ambient + diffuse) * objColor;
}