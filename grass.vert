#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 inColor;
layout (location = 4) in mat4 instanceMatrix;
//uniform mat4 model[4];
uniform mat4 view;
uniform mat4 projection;

// uniform vec3 offsets[4];

out vec2 TexCoords;
// out vec4 Color;
void main()
{
	gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);
    TexCoords = aTexCoords;
    // Color = inColor;
}