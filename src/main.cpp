#include "config.h"

int main() {

    // Initialize GLFW + window

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
        }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "basic_window", NULL, NULL);

    if (window == NULL) {
        std::cout << "GLFW failed to create window" << std::endl;
        glfwTerminate();
        return -1;
        }

    glfwMakeContextCurrent(window);

    // Initialize GLAD + OpenGL

    gladLoadGL();

    glViewport(0, 0, 1920, 1080);

    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
    };