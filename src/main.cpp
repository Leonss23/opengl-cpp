#include "config.h"

int main() {
    GLFWwindow* window = windowInit();

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

    cleanupGlfw(window);
    return 0;
    };

