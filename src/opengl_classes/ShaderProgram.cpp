#include "ShaderProgram.h"

void handleProgramLinkError(unsigned int program);

ShaderProgram::ShaderProgram(Shader shaders[], unsigned int shadersSize) {
    ID = glCreateProgram();

    for (int i = 0; i < shadersSize; i++) {
        glAttachShader(ID, shaders[i].ID);
        }
    glLinkProgram(ID);
    handleProgramLinkError(ID);
    }

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
    Shader vertexShader(vertexFile, GL_VERTEX_SHADER);
    Shader fragmentShader(fragmentFile, GL_FRAGMENT_SHADER);
    ID = glCreateProgram();

    glAttachShader(ID, vertexShader.ID);
    glAttachShader(ID, fragmentShader.ID);

    glLinkProgram(ID);
    handleProgramLinkError(ID);
    vertexShader.Delete();
    fragmentShader.Delete();
    }

void ShaderProgram::Use() {
    glUseProgram(ID);
    }

void ShaderProgram::Delete() {
    glDeleteProgram(ID);
    }

void handleProgramLinkError(unsigned int program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }