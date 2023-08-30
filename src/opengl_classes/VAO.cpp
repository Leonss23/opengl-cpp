#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
    }

void VAO::LinkAttrib(BufferObject& VBO, GLuint layout, GLuint stride, GLenum type, GLsizeiptr strideSize, void* offset) {
    glVertexAttribPointer(layout, stride, type, GL_FALSE, strideSize, offset);
    glEnableVertexAttribArray(layout);
    }

void VAO::Bind() {
    glBindVertexArray(ID);
    }

void VAO::Unbind() {
    glBindVertexArray(0);
    }

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID);
    }