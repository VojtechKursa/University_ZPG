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

uniform float ambientCoeficient = 1;
uniform float diffusionCoeficient = 1;

uniform vec4 objColor = vec4(0.385, 0.647, 0.812, 1.0);

out vec4 fragColor;

void main (void)
{
    fragColor = vec4(0,0,0,1);
    Light light;
    
    for(int i = 0; i < lightCount; i++)
    {
        light = lights[i];

        vec4 lightColor4 = vec4(light.lightColor, 1.0);

        vec3 lightVector = light.position - (worldPos.xyz / worldPos.w);

        float dotProduct = max(dot(normalize(lightVector), normalize(worldNor)), 0.0);
        vec4 diffuse = dotProduct * lightColor4 * diffusionCoeficient;
        
        vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * ambientCoeficient;

        float lightDistance = length(lightVector);
        float attenuation = light.lightStrength / (light.constantAttCoeficient + light.linearAttCoeficient * lightDistance + light.quadraticAttCoeficient * lightDistance * lightDistance);

        fragColor += diffuse * attenuation * objColor;
    }

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * ambientCoeficient;
    fragColor += ambient * objColor;
}