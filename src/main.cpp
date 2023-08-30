#include "config.h"

int main() {
    GLFWwindow* window = windowInit();

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

    ShaderProgram ShaderProgram("default.vert", "default.frag");

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
    GLuint scaleUniform = glGetUniformLocation(ShaderProgram.ID, "scale");

    // Drawing settings
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Texture
    int texWidth, texHeight, texColorChannelCount;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* texData = stbi_load("res/textures/don_trolleone.png", &texWidth, &texHeight, &texColorChannelCount, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texData);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(ShaderProgram.ID, "tex0");
    ShaderProgram.Use();
    glUniform1i(tex0Uni, 0);

    while (!glfwWindowShouldClose(window)) {
        // logic
        processInput(window);

        // rendering
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ShaderProgram.Use();
        glUniform1f(scaleUniform, 1.0f);
        VAO1.Bind();
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

        // submit
        glfwSwapBuffers(window);
        glfwPollEvents();
        }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    glDeleteTextures(1, &texture);
    ShaderProgram.Delete();

    cleanupGlfw(window);
    return 0;
    };
