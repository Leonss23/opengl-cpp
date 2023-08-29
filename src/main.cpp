#include "config.h"

int main() {
    GLFWwindow* window = windowInit();

    // Vertex Data
    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
        };
    GLuint stride = 3;
    GLsizei strideSize = stride * sizeof(vertices[0]);
    GLuint indices[] = {
        0, 1, 2
        };
    GLuint indicesCount = sizeof(indices) / sizeof(indices[0]);

    ShaderProgram ShaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    BufferObject VBO1(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    BufferObject EBO1(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0, indicesCount, strideSize);

    VBO1.Unbind();
    VAO1.Unbind();

    // Drawing settings
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        // logic
        processInput(window);

        // rendering
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ShaderProgram.Use();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

        // submit
        glfwSwapBuffers(window);
        glfwPollEvents();
        }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    ShaderProgram.Delete();

    cleanupGlfw(window);
    return 0;
    };
