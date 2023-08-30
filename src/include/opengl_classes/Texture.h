#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string.h>

#include "ShaderProgram.h"

class Texture {
public:
    GLuint ID;
    GLenum type;
    Texture(const char* fileName, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    void texUnit(ShaderProgram& shaderProgram, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
    };
