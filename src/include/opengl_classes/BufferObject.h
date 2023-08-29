#pragma once

#include <glad/glad.h>

class BufferObject {
public:
    GLuint ID;
    GLenum TYPE;
    BufferObject(GLenum type, GLfloat* data, GLsizeiptr size);
    BufferObject(GLenum type, GLuint* data, GLsizeiptr size);
    void Bind();
    void Unbind();
    void Delete();
    };