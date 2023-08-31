#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(int init_width, int init_height, const char* title) {
    width = init_width;
    height = init_height;
    // GLFW Init
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(-1);
        }

    // Window settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW Window Init
    handle = glfwCreateWindow(width, height, title, NULL, NULL);

    if (handle == NULL) {
        std::cout << "GLFW failed to create window" << std::endl;
        glfwTerminate();
        exit(-1);
        }


    // Proper window resizing
    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);

    // GLFW OpenGL Context Init
    glfwMakeContextCurrent(handle);

    // GLAD Init
    gladLoadGL();

    // OpenGL Setup
    glViewport(0, 0, width, height);
    }

void Window::Delete() {
    glfwDestroyWindow(handle);
    glfwTerminate();
    }

void Window::Submit() {
    glfwSwapBuffers(handle);
    glfwPollEvents();
    }

int Window::ShouldClose() {
    return glfwWindowShouldClose(handle);
    }

void Window::Update() {
    // Update
    glfwGetWindowSize(handle, &width, &height);

    // Input
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(handle, true);
        }
    }

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    }