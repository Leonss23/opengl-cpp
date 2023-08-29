#pragma once

#include <glad/glad.h>
#include "BufferObject.h"

class VAO {
public:
    GLuint ID;
    VAO();
    void LinkVBO(BufferObject VBO, GLuint layout, GLuint indicesCount, GLsizei strideSize);
    void Bind();
    void Unbind();
    void Delete();
    };