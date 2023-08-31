#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    GLFWwindow* handle;
    int width, height;
    Window(int width, int height, const char* title);
    void Delete();
    void Update();
    int ShouldClose();
    void Submit();
    };