#include "Shader.h"

#include <iostream>

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename) {
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        throw(errno);
    }
    std::ostringstream oss;
    oss << in.rdbuf();
    return oss.str();
}

// Constructor that builds the Shader Program from two different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    // Read vertexFile and fragmentFile and store the strings
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create shader objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Attach shader source code to shader objects
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

    // Compile vertex shader
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    // Compile fragment shader
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    // Create shader program
    ID = glCreateProgram();
    // Attach vertex and fragment shaders to the shader program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Link shader program
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // Delete shader objects as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Check for compilation/linking errors and print error message
void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            throw(errno);
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            throw(errno);
        }
    }
}

// Activate the Shader Program
void Shader::Activate() {
    glUseProgram(ID);
}

// Delete the Shader Program
void Shader::Delete() {
    glDeleteProgram(ID);
}

// Set a 4x4 matrix uniform
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// Set a 3-component vector uniform
void Shader::setVec4(const std::string& name, const glm::vec3& vec) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z, 1.0f);
}

// Set a 3-component vector uniform
void Shader::setVec3(const std::string& name, const glm::vec3& vec) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z);
}

// Set a floating-point uniform
void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

// Set an integer uniform
void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
