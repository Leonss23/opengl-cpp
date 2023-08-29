#pragma once

#include <string>
#include <glad/glad.h>
#include "utils.h"

class Shader {
public:
    GLuint ID;
    GLenum TYPE;
    Shader(const char* filename, GLenum type);
    void Delete();
    };