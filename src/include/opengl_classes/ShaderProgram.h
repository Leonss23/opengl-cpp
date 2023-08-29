#pragma once

#include <glad/glad.h>
#include "utils.h"
#include "Shader.h"

class ShaderProgram {
public:
    GLuint ID;
    ShaderProgram(const char* vertexFile, const char* fragmentFile);
    ShaderProgram(Shader shaders[], unsigned int shadersSize);
    void Delete();
    void Use();
    };