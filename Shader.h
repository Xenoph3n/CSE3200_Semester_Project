#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

class Shader {
public:
    // Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();

	void setMat4(const std::string &name, const glm::mat4 &mat) const;

	void setVec4(const std::string &name, const glm::vec3 &vec) const;

	void setVec3(const std::string &name, const glm::vec3 &vec) const;

	void setFloat(const std::string &name, float value) const;

	void setInt(const std::string &name, int value) const;

	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	
	void setBool(const std::string &name, bool value) const;

    void setPBRMaterial(const glm::vec3& albedo, float metallic, float roughness, float ao) const;

    void setPBRTextures(/* Texture parameters */) const;

private:
    // Utility function to read a text file and output its contents as a string
    std::string get_file_contents(const char* filename);

    // Utility function to check for compilation/linking errors
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif
