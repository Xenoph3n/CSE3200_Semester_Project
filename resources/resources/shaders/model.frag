#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 Color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;

void main()
{    
    // FragColor = texture(texture_diffuse1, TexCoords);
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
