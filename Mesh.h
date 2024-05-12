#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"aCamera.h"
#include"Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#include <glm/gtx/vector_angle.hpp>
#include <vector>

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	
	// Store VAO in public so it can be used in the Draw function
	VAO VAO1;
	std::vector<glm::mat4> models;

	// Initializes the mesh
	Mesh(
		std::vector <Vertex>& vertices, 
		std::vector <GLuint>& indices, 
		std::vector <Texture>& texture,
		bool apply_tex = false,
		bool instance = false,
		const std::vector<glm::mat4> &models = std::vector<glm::mat4>()
		);
	
	// Draws the mesh
	void Draw
	(
		Shader& shader, 
		bool check = false,
		bool instance = false,
		const std::vector<glm::mat4> &models = std::vector<glm::mat4>(),
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(-0.5f, 0.2f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
};
#endif