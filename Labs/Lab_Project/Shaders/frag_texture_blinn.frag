#version 400



struct Light
{
    float lightStrength;
    float constantAttCoeficient;
    float linearAttCoeficient;
    float quadraticAttCoeficient;

    int type;

    vec3 position;
    vec3 direction;
    float edge_cos;

    vec3 lightColor;

    bool disabled;
};



vec3 getLightVector(Light light, vec3 worldPos)
{
    if(light.type == 0 || light.type == 2)   // point light or spot light
    {
        return light.position - worldPos;
    }
    else
    {
        return -light.direction;
    }
}

float getAttenuation(float lightDistance, Light light)
{
    return light.lightStrength / (light.constantAttCoeficient + light.linearAttCoeficient * lightDistance + light.quadraticAttCoeficient * lightDistance * lightDistance);
}

vec4 lambert(vec3 lightVector, vec3 worldNor, vec4 lightColor4, float diffusionCoeficient)
{
    float dotProduct = max(dot(normalize(lightVector), normalize(worldNor)), 0.0);
    return dotProduct * lightColor4 * diffusionCoeficient;
}

vec4 blinn(vec3 lightVectorNorm, vec3 worldNorNorm, vec3 viewDir, vec4 lightColor4, float specularCoeficient, float shininessConstant)
{
    vec3 halfwayDir = normalize(lightVectorNorm + viewDir);
    
    if (dot(worldNorNorm, lightVectorNorm) < 0.0)
    {
        return vec4 (0.0 , 0.0 , 0.0 , 0.0);
    }
    else
    {
        float spec = pow(max(dot(worldNorNorm, halfwayDir), 0.0), shininessConstant);
        return specularCoeficient * spec * lightColor4;
    }
}

float spotlightDropoffSharp(Light light, vec3 lightVectorNorm)
{
    if(light.type == 2) // spotlight
    {
        float offset = max(dot(-lightVectorNorm, light.direction), 0.0);

        return offset > light.edge_cos ? 1.0 : 0.0;
    }
    else
    {
        return 1.0;
    }
}





in vec4 worldPos;
in vec3 worldNor;
in vec2 uvCoord;

uniform vec3 cameraPosWorld;

uniform Light lights[10];
uniform int lightCount = 0;

uniform float ambientCoeficient = 1;
uniform float diffusionCoeficient = 1;
uniform float specularCoeficient = 2;
uniform float shininessConstant = 32;

uniform vec3 highlightColor = vec3(0,0,0);

uniform sampler2D textureUnitId;

out vec4 fragColor;



void main (void)
{
    vec4 objColor = texture(textureUnitId, uvCoord);
    
    vec3 worldPos3 = worldPos.xyz / worldPos.w;
    vec3 worldNorNorm = normalize(worldNor);

    fragColor = vec4(0,0,0,1);
    Light light;
    
    for(int i = 0; i < lightCount; i++)
    {
        light = lights[i];

        if(light.disabled)
            continue;

        vec4 lightColor4 = vec4(light.lightColor, 1.0);

        vec3 lightVector = getLightVector(light, worldPos3);
        vec3 lightVectorNorm = normalize(lightVector);
        vec3 viewDir = normalize(cameraPosWorld - worldPos3);

        vec4 specular = blinn(lightVectorNorm, worldNorNorm, viewDir, lightColor4, specularCoeficient, shininessConstant);

        vec4 diffuse = lambert(lightVectorNorm, worldNorNorm, lightColor4, diffusionCoeficient);
        
        float attenuation = getAttenuation(length(lightVector), light);
        float spotlightDropoff = spotlightDropoffSharp(light, normalize(lightVector));

        fragColor += (diffuse + specular) * attenuation * spotlightDropoff * objColor;
    }

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * ambientCoeficient;
    fragColor += ambient * objColor + vec4(highlightColor, 0);
}