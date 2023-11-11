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
    float edge_cos;     // cosine of the edge angle

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

vec4 lambert(vec3 lightVectorNorm, vec3 worldNorNorm, vec4 lightColor4, float diffusionCoeficient)
{
    float dotProduct = max(dot(lightVectorNorm, worldNorNorm), 0.0);
    return dotProduct * lightColor4 * diffusionCoeficient;
}

vec4 phong(vec3 lightVectorNorm, vec3 worldNorNorm, vec3 viewDir, vec4 lightColor4, float specularCoeficient, float shininessConstant)
{
    if (dot(worldNorNorm, lightVectorNorm) < 0.0)
    {
        return vec4 (0.0 , 0.0 , 0.0 , 0.0);
    }
    else
    {
        float spec = pow(max(dot(viewDir, reflect(-lightVectorNorm, worldNorNorm)), 0.0), shininessConstant);
        return specularCoeficient * spec * lightColor4;
    }
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
