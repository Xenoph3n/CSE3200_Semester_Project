#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures, bool apply_text)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	
	if (apply_text) {
		Mesh::textures = textures;
	}

	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO1
	VAO1.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO1.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


// void Mesh::Draw
// (
// 	Shader& shader, 
// 	Camera& camera,
// 	glm::mat4 matrix,
// 	glm::vec3 translation, 
// 	glm::quat rotation, 
// 	glm::vec3 scale
// )
// {
// 	// Bind shader to be able to access uniforms
// 	shader.Activate();
// 	VAO1.Bind();

// 	// Take care of the camera Matrix
// 	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
// 	camera.Matrix(shader, "camMatrix");

// 	// Initialize matrices
// 	glm::mat4 trans = glm::mat4(1.0f);
// 	glm::mat4 rot = glm::mat4(1.0f);
// 	glm::mat4 sca = glm::mat4(1.0f);

// 	// Transform the matrices to their correct form
// 	trans = glm::translate(trans, translation);
// 	rot = glm::mat4_cast(rotation);
// 	sca = glm::scale(sca, scale);

// 	// Push the matrices to the vertex shader
// 	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
// 	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
// 	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
// 	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

// 	// Draw the actual mesh
// 	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
// }

void Mesh::Draw
(
	Shader& shader, 
	bool check,
	glm::mat4 matrix,
	glm::vec3 translation, 
	glm::quat rotation, 
	glm::vec3 scale

)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO1.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	if (!check) {
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			std::string num;
			std::string type = textures[i].type;
			if (type == "diffuse")
			{
				num = std::to_string(numDiffuse++);
			}
			else if (type == "specular")
			{
				num = std::to_string(numSpecular++);
			}
			textures[i].texUnit(shader, (type + num).c_str(), i);
			textures[i].Bind();
		}
	}
	
	// Take care of the camera Matrix
	// glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// camera.Matrix(shader, "camMatrix");

	// Initialize matrices
	// glm::mat4 trans = glm::mat4(1.0f);
	// glm::mat4 rot = glm::mat4(1.0f);
	// glm::mat4 sca = glm::mat4(1.0f);

	// // // // Transform the matrices to their correct form
	// trans = glm::translate(trans, translation);
	// rot = glm::mat4_cast(rotation);
	// sca = glm::scale(sca, scale);

	// // // // Push the matrices to the vertex shader
	// glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	// glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	// glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	// glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


