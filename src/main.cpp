#include "config.h"

int main() {
    Window window(1280, 720, "Learning OpenGL");

    // Vertex Data
    GLfloat vertices[] = {
        //  Position            /   Color               /   Texture         //  
        //  x       y       z   /   r       g       b   /   x       y       //  
           -0.5f,   0.0f,   0.5f,   1.0f,   0.0f,   0.0f,   0.0f,   0.0f,   //  near-left   red
           -0.5f,   0.0f,  -0.5f,   0.0f,   1.0f,   0.0f,   5.0f,   0.0f,   //  far-left    green
            0.5f,   0.0f,   0.5f,   0.0f,   0.0f,   1.0f,   5.0f,   0.0f,   //  near-right  blue
            0.5f,   0.0f,  -0.5f,   0.0f,   0.0f,   0.0f,   0.0f,   0.0f,   //  far-right   black
            0.0f,   0.75f,   0.0f,   1.0f,   1.0f,   1.0f,   2.5f,   5.0f,   //  top         white
        };
    GLuint indices[] = {
        0, 1, 2,    // near-left floor
        1, 2, 3,    // far-right floor
        0, 1, 4,    // left  wall
        0, 2, 4,    // near wall
        1, 3, 4,    // far wall
        2, 3, 4,    // right wall
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

    GLuint modelUni = glGetUniformLocation(shaderProgram.ID, "model");
    GLuint viewUni = glGetUniformLocation(shaderProgram.ID, "view");
    GLuint projUni = glGetUniformLocation(shaderProgram.ID, "proj");

    // Drawing settings
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Texture
    Texture texture1("don_trolleone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture1.texUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);


    Camera camera(window.width, window.height, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!window.ShouldClose()) {
        // logic
        window.Update();

        // rendering
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Use();

        camera.Inputs(window.handle);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        VAO1.Bind();
        texture1.Bind();
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

        // submit
        window.Submit();
        }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    texture1.Delete();
    shaderProgram.Delete();

    window.Delete();
    return 0;
    };
