#version 400

in vec4 worldPos;
in vec3 worldNor;

out vec4 fragColor;

void main (void)
{
    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    vec3 lightVector = worldPos - lightPosition;

    float dotProduct = max(dot(normalize(lightVector), normalize(worldNor)), 0.0);
    
    vec4 objColor = vec4( 0.385, 0.647, 0.812, 1.0);
    vec4 diffuse = dotProduct * objColor;
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);

    fragColor = ambient + diffuse;
}