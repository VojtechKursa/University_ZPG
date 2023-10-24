#version 400

in vec4 worldPos;
in vec3 worldNor;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosWorld;

out vec4 fragColor;

void main (void)
{
    vec4 objColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec4 lightColor4 = vec4(lightColor, 1.0);
    float specularStrength = 2;
    float shininessConstant = 32;

    vec3 worldPos3 = worldPos.xyz / worldPos.w;
    vec3 worldNorNor = normalize(worldNor);

    vec3 lightVector = normalize(lightPosition - worldPos3);
    vec3 viewDir = normalize(cameraPosWorld - worldPos3);
    vec3 halfwayDir = normalize(lightVector + viewDir);
    
    float spec = pow(max(dot(worldNorNor, halfwayDir), 0.0), shininessConstant);
    vec4 specular = specularStrength * spec * lightColor4;

    float dotProduct = max(dot(lightVector, worldNorNor), 0.0);
    vec4 diffuse = dotProduct * lightColor4;

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    fragColor = (ambient + diffuse + specular) * objColor;
}