#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;

// out vec2 texCoord;
out vec4 clipSpace;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;


void main()
{
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	// texCoord = aTex;
	clipSpace = projection * view * model * vec4(aPos, 1.0);
	// Outputs the positions/coordinates of all vertices
	gl_Position = clipSpace;
}