#version 400

in vec4 worldPos;
in vec3 worldNor;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosWorld;

uniform float constantAttCoeficient = 1;
uniform float linearAttCoeficient = 0.1;
uniform float quadraticAttCoeficient = 0.01;

uniform float ambientCoeficient = 1;
uniform float diffusionCoeficient = 1;
uniform float specularCoeficient = 2;
uniform float shininessConstant = 32;

uniform vec4 objColor = vec4(0.385, 0.647, 0.812, 1.0);

out vec4 fragColor;

void main (void)
{
    vec4 lightColor4 = vec4(lightColor, 1.0);

    vec3 worldPos3 = worldPos.xyz / worldPos.w;
    vec3 worldNorNor = normalize(worldNor);

    vec3 lightVector = lightPosition - worldPos3;
    vec3 lightVectorNorm = normalize(lightVector);
    vec3 viewDir = normalize(cameraPosWorld - worldPos3);
    vec3 halfwayDir = normalize(lightVectorNorm + viewDir);
    
    vec4 specular;
    if (dot(worldNor, lightVector) < 0.0)
    {
        specular = vec4 (0.0 , 0.0 , 0.0 , 0.0);
    }
    else
    {
        float spec = pow(max(dot(worldNorNor, halfwayDir), 0.0), shininessConstant);
        specular = specularCoeficient * spec * lightColor4;
    }
    
    float dotProduct = max(dot(lightVectorNorm, worldNorNor), 0.0);
    vec4 diffuse = dotProduct * lightColor4 * diffusionCoeficient;

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * ambientCoeficient;

    float lightDistance = length(lightVector);
    float attenuation = 1 / (constantAttCoeficient + linearAttCoeficient * lightDistance + quadraticAttCoeficient * lightDistance * lightDistance);

    fragColor = (((diffuse + specular) * attenuation) + ambient) * objColor;
}