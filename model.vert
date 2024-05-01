#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 inColor;


out vec2 TexCoords;
out vec3 crntPos;
out vec3 Normal;
out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 position = projection * view * model * vec4(aPos, 1.0);
    TexCoords = aTexCoords;   

    crntPos = vec3(position);

    Normal = aNormal;

    color = inColor;
 
    gl_Position = position;
}