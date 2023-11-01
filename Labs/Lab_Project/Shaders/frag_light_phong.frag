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

    vec3 lightColor;
};



in vec4 worldPos;
in vec3 worldNor;

uniform Light lights[10];
uniform int lightCount = 0;

uniform vec3 cameraPosWorld;

uniform float ambientCoeficient = 1;
uniform float diffusionCoeficient = 1;
uniform float specularCoeficient = 2;
uniform float shininessConstant = 32;

uniform vec4 objColor = vec4(0.385, 0.647, 0.812, 1.0);

out vec4 fragColor;

void main (void)
{
    vec3 worldPos3 = worldPos.xyz / worldPos.w;
    vec3 worldNorNor = normalize(worldNor);
    fragColor = vec4(0,0,0,1);
    Light light;

    for(int i = 0; i < lightCount; i++)
    {
        light = lights[i];

        vec4 lightColor4 = vec4(light.lightColor, 1.0);

        vec3 lightVector = light.position - worldPos3;
        vec3 lightVectorNorm = normalize(lightVector);
        vec3 viewDir = normalize(cameraPosWorld - worldPos3);
        vec3 reflectDir = reflect(-lightVectorNorm, worldNorNor);

        vec4 specular;
        if (dot(worldNor, lightVector) < 0.0)
        {
            specular = vec4 (0.0 , 0.0 , 0.0 , 0.0);
        }
        else
        {
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininessConstant);
            specular = specularCoeficient * spec * lightColor4;
        }

        float dotProduct = max(dot(lightVectorNorm, worldNorNor), 0.0);
        vec4 diffuse = dotProduct * lightColor4 * diffusionCoeficient;

        vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * ambientCoeficient;

        float lightDistance = length(lightVector);
        float attenuation = light.lightStrength / (light.constantAttCoeficient + light.linearAttCoeficient * lightDistance + light.quadraticAttCoeficient * lightDistance * lightDistance);

        fragColor = (diffuse + specular) * attenuation * objColor;
    }

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * ambientCoeficient;
    fragColor += ambient * objColor;
}