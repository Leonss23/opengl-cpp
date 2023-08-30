#include "Texture.h"

Texture::Texture(const char* fileName, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    type = texType;

    int texWidth, texHeight, texColorChannelCount;
    stbi_set_flip_vertically_on_load(true);
    const char* fullPath = (std::string("res/textures/") + fileName).c_str();
    unsigned char* texData = stbi_load(fullPath, &texWidth, &texHeight, &texColorChannelCount, 0);

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, GL_RGBA, texWidth, texHeight, 0, format, pixelType, texData);
    glGenerateMipmap(texType);

    stbi_image_free(texData);
    glBindTexture(texType, 0);
    }

void Texture::texUnit(ShaderProgram& shaderProgram, const char* uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(shaderProgram.ID, uniform);
    shaderProgram.Use();
    glUniform1i(texUni, unit);
    }

void Texture::Bind() {
    glBindTexture(type, ID);
    }

void Texture::Unbind() {
    glBindTexture(type, 0);
    }

void Texture::Delete() {
    glDeleteTextures(1, &ID);
    }