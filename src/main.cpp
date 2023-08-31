#include "config.h"

int main() {
    Window window(1280, 720, "Learning OpenGL");

    // Vertex Data
    GLfloat vertices[] = {
        //  Position            /   Color               /   Texture         //  
        //  x       y       z   /   r       g       b   /   x       y       //  
            -0.5f,  -0.5f,  0.0f,   1.0f,   0.0f,   0.0f,   0.0f,   0.0f,   //  bottom-left     red
            -0.5f,  0.5f,   0.0f,   0.0f,   1.0f,   0.0f,   0.0f,   1.0f,   //  top-left        green
            0.5f,   0.5f,   0.0f,   0.0f,   0.0f,   1.0f,   1.0f,   1.0f,   //  top-right       blue
            0.5f,   -0.5f,  0.0f,   1.0f,   1.0f,   1.0f,   1.0f,   0.0f,   //  bottom-right    white
        };
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
        };
    GLuint indicesCount = sizeof(indices) / sizeof(indices[0]);
    GLenum attrType = GL_FLOAT;
    GLuint vertStride = 8;
    GLsizeiptr vertSize = vertStride * sizeof(vertices[0]);

    ShaderProgram shaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    BufferObject VBO1(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    BufferObject EBO1(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, attrType, vertSize, 0);
    VAO1.LinkAttrib(VBO1, 1, 3, attrType, vertSize, (void*)(3 * sizeof(GLfloat)));
    VAO1.LinkAttrib(VBO1, 2, 2, attrType, vertSize, (void*)(6 * sizeof(GLfloat)));

    VBO1.Unbind();
    VAO1.Unbind();
    EBO1.Unbind();

    // Uniforms
    GLuint scaleUniform = glGetUniformLocation(shaderProgram.ID, "scale");

    // Drawing settings
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Texture
    Texture texDonTrolleone("don_trolleone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texDonTrolleone.texUnit(shaderProgram, "tex0", 0);

    while (!window.ShouldClose()) {
        // logic
        window.Update();

        // rendering
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 proj(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(window.width / window.height), 0.1f, 100.0f);

        glUniform1f(scaleUniform, 1.0f);
        VAO1.Bind();
        texDonTrolleone.Bind();
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

        // submit
        window.Submit();
        }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    texDonTrolleone.Delete();
    shaderProgram.Delete();

    window.Delete();
    return 0;
    };
