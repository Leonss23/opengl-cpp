#include "deps.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const int SCR_WIDTH = 1000;
const int SCR_HEIGHT = 800;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learning OpenGL :D", NULL, NULL);

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
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    while (!glfwWindowShouldClose(window)) {
        // logic
        processInput(window);

        // rendering
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // submit
        glfwSwapBuffers(window);
        glfwPollEvents();
        }

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
