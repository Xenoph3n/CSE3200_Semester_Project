#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
// uniform vec4 plane;

void main()
{
	vec4 position = projection * view * model * vec4(aPos, 1.0);
	texCoord = aTex;
	gl_Position = position;
}