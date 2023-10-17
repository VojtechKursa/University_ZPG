#version 400

in vec4 worldPos;
in vec3 worldNor;

out vec4 fragColor;

void main (void)
{
    vec3 lightPosition = vec3(0.0, 4.0, 0.0);
    vec4 objColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
    vec3 viewDir = vec3(1.0, 1.0, 1.0);
    float specularStrength = 1;

    vec3 lightVector = lightPosition - vec3(worldPos);

    vec3 reflectDir = reflect(-lightVector, worldNor);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = specularStrength * spec * lightColor;

    float dotProduct = max(dot(normalize(lightVector), normalize(worldNor)), 0.0);
    
    vec4 diffuse = dotProduct * lightColor;
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    fragColor = (ambient + diffuse) * objColor;
}