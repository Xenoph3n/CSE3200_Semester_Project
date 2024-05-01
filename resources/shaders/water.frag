#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec2 texCoord;
in vec4 clipSpace;

// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main() {
	vec2 ndc = (clipSpace.xy/clipSpace.w) / 2.0 + 0.5;
	vec2 reflectionTexCord = vec2(ndc.x, ndc.y);
	FragColor = texture(diffuse0, reflectionTexCord);
}