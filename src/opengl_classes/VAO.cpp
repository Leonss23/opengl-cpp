#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
    }

void VAO::LinkVBO(BufferObject& VBO, GLuint layout, GLuint indicesCount, GLsizei strideSize) {
    glVertexAttribPointer(layout, indicesCount, GL_FLOAT, GL_FALSE, strideSize, (void*)0);
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