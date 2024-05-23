#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 inColor;
layout(location = 5) in ivec4 boneIds; 
layout(location = 6) in vec4 weights;
	
out vec2 TexCoords;
out vec3 crntPos;
out vec3 Normal;
out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{

    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES) 
        {
            totalPosition = vec4(pos,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos,1.0f);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * norm;
    }

		
    mat4 viewModel = view * model;

    vec4 position = projection * view * model * vec4(aPos, 1.0);

    TexCoords = aTexCoords;   

    crntPos = vec3(position);

    Normal = aNormal;

    color = inColor;
 
    gl_Position = projection * viewModel * totalPosition;
}