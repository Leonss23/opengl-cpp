#pragma once

#include <glad/glad.h>
#include "BufferObject.h"

class VAO {
public:
    GLuint ID;
    VAO();
    void LinkAttrib(BufferObject& VBO, GLuint layout, GLuint stride, GLenum type, GLsizeiptr strideSize, void* offset);
    void Bind();
    void Unbind();
    void Delete();
    };