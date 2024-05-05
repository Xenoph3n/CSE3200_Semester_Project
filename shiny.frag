#version 330 core

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;

in vec2 TexCoords;
in vec3 crntPos;
in vec3 Normal;
in vec4 color;

struct Material {
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 camPosition;

vec4 directLight() {

    vec3 normal = normalize(Normal);
    vec3 light_direction = light.direction;
    vec3 diffuse = max(dot(normal, light_direction), 0.0f) * light.diffuse * texture(texture_diffuse1, TexCoords).rgb;

    vec3 view_direction = normalize(light.position - crntPos);
    vec3 halfway = normalize(light_direction + view_direction);

    vec3 reflection_direction = reflect(-light_direction, normal);
    
    float spec_amount = pow(max(dot(halfway, reflection_direction), 0.0f), material.shininess);
    
    vec3 specular = light.specular * spec_amount * texture(texture_specular1, TexCoords).rgb;

    vec3 ambient = light.ambient * texture(texture_diffuse1, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular;

    return vec4(result, 1.0);
}

vec4 flashLight() {

    vec3 ambient = light.ambient * texture(texture_diffuse1, TexCoords).rgb;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - crntPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb;

    vec3 viewDir = normalize(camPosition - crntPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(texture_specular1, TexCoords).rgb;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;

    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    float distance    = length(light.position - crntPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
    
    ambient *= attenuation * 100;
    diffuse *= attenuation * 100;
    specular *= attenuation * 100;

    vec3 result = ambient + diffuse + specular;

    return vec4(result, 1.0);
}
void main()
{    
    FragColor = directLight();
}