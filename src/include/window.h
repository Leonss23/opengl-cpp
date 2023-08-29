#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* windowInit();
void processInput(GLFWwindow* window);
void cleanupGlfw(GLFWwindow* window);