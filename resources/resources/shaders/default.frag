#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec2 texCoord;

// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main() {
	FragColor = texture(diffuse0, texCoord);
}