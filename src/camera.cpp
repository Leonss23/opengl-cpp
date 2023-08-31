#include "camera.h"


Camera::Camera(int width, int height, glm::vec3 position) {
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
    }

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, ShaderProgram& shaderProgram, const char* uniform) {
    glm::mat4 view(1.0f);
    glm::mat4 proj(1.0f);

    view = glm::lookAt(position, position + orientation, up);
    proj = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

    GLint uniLoc = glGetUniformLocation(shaderProgram.ID, uniform);
    glUniformMatrix4fv(uniLoc, 1, GL_FALSE, glm::value_ptr(proj * view));
    }

void Camera::Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += currentSpeed * orientation;
        }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position += currentSpeed * -glm::normalize(glm::cross(orientation, up));
        }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position += currentSpeed * -orientation;
        }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += currentSpeed * glm::normalize(glm::cross(orientation, up));
        }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += currentSpeed * up;
        }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        position += currentSpeed * -up;
        }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        currentSpeed = speed * 2;
        }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        currentSpeed = speed;
        }


    // Handles mouse inputs
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Hides mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevents camera from jumping on the first click
        if (firstClick) {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
            }

        // Stores the coordinates of the cursor
        double mouseX;
        double mouseY;
        // Fetches the coordinates of the cursor
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
        // and then "transforms" them into degrees 
        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        // Calculates upcoming vertical change in the Orientation
        glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

        // Decides whether or not the next vertical Orientation is legal or not
        if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
            orientation = newOrientation;
            }

        // Rotates the Orientation left and right
        orientation = glm::rotate(orientation, glm::radians(-rotY), up);

        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
        glfwSetCursorPos(window, (width / 2), (height / 2));
        }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        // Unhides cursor since camera is not looking around anymore
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Makes sure the next time the camera looks around it doesn't jump
        firstClick = true;
        }
    }