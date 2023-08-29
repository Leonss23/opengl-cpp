#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void initGlfw();

const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;

GLFWwindow* windowInit() {
    // GLFW Init
    initGlfw();

    // Window settings
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
        exit(-1);
        }

    // Proper window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLFW OpenGL Context Init
    glfwMakeContextCurrent(window);

    // GLAD Init
    gladLoadGL();

    // OpenGL Setup
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    return window;
    }

void initGlfw() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(-1);
        }
    }

void cleanupGlfw(GLFWwindow* window) {
    glfwDestroyWindow(window);
    glfwTerminate();
    }

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    }

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        }
    }
