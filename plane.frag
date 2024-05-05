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

uniform vec4 lightColor;

uniform vec3 camPosition;

vec4 direcLight()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPosition - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(texture_diffuse1, TexCoords) * (diffuse + ambient) + texture(texture_specular1, TexCoords).r * specular) * lightColor;
}


void main()
{    
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}