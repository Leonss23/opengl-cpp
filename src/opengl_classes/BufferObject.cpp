#include "BufferObject.h"

// VBO
BufferObject::BufferObject(GLenum type, GLfloat* data, GLsizeiptr size) {
    TYPE = type;
    glGenBuffers(1, &ID);
    glBindBuffer(TYPE, ID);
    glBufferData(TYPE, size, data, GL_STATIC_DRAW);
    }
// EBO
BufferObject::BufferObject(GLenum type, GLuint* data, GLsizeiptr size) {
    TYPE = type;
    glGenBuffers(1, &ID);
    glBindBuffer(TYPE, ID);
    glBufferData(TYPE, size, data, GL_STATIC_DRAW);
    }

void BufferObject::Bind() {
    glBindBuffer(TYPE, ID);
    }

void BufferObject::Unbind() {
    glBindBuffer(TYPE, 0);
    }

void BufferObject::Delete() {
    glDeleteBuffers(1, &ID);
    }
