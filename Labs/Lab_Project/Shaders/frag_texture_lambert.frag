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

uniform Light lights[10];
uniform int lightCount = 0;

uniform float ambientCoeficient = 1;
uniform float diffusionCoeficient = 1;

uniform sampler2D textureUnitId;

out vec4 fragColor;



void main (void)
{
    vec4 objColor = texture(textureUnitId, uvCoord);

    fragColor = vec4(0,0,0,1);
    Light light;
    
    for(int i = 0; i < lightCount; i++)
    {
        light = lights[i];

        if(light.disabled)
            continue;

        vec4 lightColor4 = vec4(light.lightColor, 1.0);

        vec3 lightVector = getLightVector(light, (worldPos.xyz / worldPos.w));

        vec4 diffuse = lambert(lightVector, worldNor, lightColor4, diffusionCoeficient);
        
        float attenuation = getAttenuation(length(lightVector), light);
        float spotlightDropoff = spotlightDropoffSharp(light, normalize(lightVector));

        fragColor += diffuse * attenuation * spotlightDropoff * objColor;
    }

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * ambientCoeficient;
    fragColor += ambient * objColor;
}