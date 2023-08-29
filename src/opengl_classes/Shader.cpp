#include "Shader.h"

void handleShaderCompileError(unsigned int shader);

#define SHADER_PATH "res/shaders/"

Shader::Shader(const char* filename, GLenum type) {
    TYPE = type;
    ID = glCreateShader(type);
    // get shader code from file
    std::string code = get_file_contents(SHADER_PATH, filename);
    const char* src = code.c_str();

    glShaderSource(ID, 1, &src, NULL);
    glCompileShader(ID);
    handleShaderCompileError(ID);
    }

void Shader::Delete() {
    glDeleteShader(ID);
    }

void handleShaderCompileError(unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }