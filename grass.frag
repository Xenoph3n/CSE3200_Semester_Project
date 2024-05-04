#version 330 core

out vec4 FragColor;

uniform sampler2D diffuse0;

in vec2 TexCoords;

void main()
{
	vec4 texel = texture(diffuse0, TexCoords);
    if(texel.a < 0.5)
        discard;

    FragColor = texel;
}