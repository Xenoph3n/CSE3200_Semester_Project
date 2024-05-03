#ifndef VERTEX_H
#define VERTEX_H


// Structure to standardize the vertices used in the meshes
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec4 color;
	glm::vec2 texUV;
};

#endif