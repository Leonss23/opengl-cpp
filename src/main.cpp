#include "deps.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int newShader(const char* shaderSource, GLenum shaderType);
unsigned int newShaderProgram(GLuint* shaders, uint16_t shaderCount);

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;

int main() {
    // GLFW Init
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
        }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW Window Init
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Learning OpenGL :D", NULL, NULL);

    if (window == NULL) {
        std::cout << "GLFW failed to create window" << std::endl;
        glfwTerminate();
        return -1;
        }

    // Proper window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLFW OpenGL Context Init
    glfwMakeContextCurrent(window);

    // GLAD Init
    gladLoadGL();

    // OpenGL Setup
    glViewport(0, 0, 1920, 1080);

    ShaderProgram shaderProgram = ShaderProgram("default.vert", "default.frag");

    // Set up GL buffers
    // square vertices
    float vertices[] = {
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
        };
    // square indices
    unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
        };

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);

    VBO1.Unbind();
    VAO1.Unbind();
    EBO1.Unbind();


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    while (!glfwWindowShouldClose(window)) {
        // logic
        processInput(window);

        // rendering
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // submit
        glfwSwapBuffers(window);
        glfwPollEvents();
        }

    // Clean Up OpenGL
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
    };

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    }

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        }
    }
