#version 330 core

out vec4 FragColor;

in vec3 FragPos; // Position of the fragment
in vec3 Normal;  // Normal of the fragment

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform bool spotlightOn;
uniform vec3 spotlightDirection;

void main()
{
    vec3 ambient = 0.1 * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = ambient + diffuse;

    if (spotlightOn)
    {
        // Implement spotlight effect
        vec3 spotlightDir = normalize(spotlightDirection);
        float theta = dot(lightDir, spotlightDir);
        float epsilon = 0.9; // Spotlight angle

        if (theta > epsilon)
        {
            result *= vec3(1.0); // Spotlight effect
        }
        else
        {
            result *= vec3(0.0); // No light outside spotlight
        }
    }

   FragColor = vec4(result, 1.0);
 //   FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}