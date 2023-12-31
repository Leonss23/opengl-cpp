#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderProgram.h"

class Camera {
public:
    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstClick = true;

    int width;
    int height;

    float speed = 0.02f;
    float currentSpeed = speed;
    float sensitivity = 80.0f;

    Camera(int width, int height, glm::vec3 position);

    void Matrix(float FOVdeg, float nearPlane, float farPlane, ShaderProgram& shaderProgram, const char* uniform);

    void Inputs(GLFWwindow* window);
    };