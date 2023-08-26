#include "ShaderProgram.h"

GLuint newShader(const char* shaderSource, GLenum shaderType);
GLuint newShaderProgram(GLuint* shaders, unsigned int shaderCount);

std::string get_file_contents(const char* filename) {
    std::string filepath = "shaders/" + std::string(filename);
    std::ifstream in(filepath, std::ios::binary);
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
        }
    std::cerr << "couldn't find " << filename << std::endl;
    throw(errno);
    }

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = newShader(vertexSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = newShader(fragmentSource, GL_FRAGMENT_SHADER);
    unsigned int shaders[] = { vertexShader, fragmentShader };

    ID = newShaderProgram(shaders, sizeof(shaders) / sizeof(shaders[0]));
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    }

void ShaderProgram::Use() {
    glUseProgram(ID);
    }

void ShaderProgram::Delete() {
    glDeleteProgram(ID);
    }

void handleShaderCompileError(unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

GLuint newShader(const GLchar* shaderSource, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    handleShaderCompileError(shader);
    return shader;
    }

void handleProgramLinkError(unsigned int program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

GLuint newShaderProgram(GLuint shaders[], unsigned int shaderCount) {
    GLuint shaderProgram = glCreateProgram();
    for (int i = 0; i < shaderCount; i++) {
        glAttachShader(shaderProgram, shaders[i]);
        }
    glLinkProgram(shaderProgram);
    handleProgramLinkError(shaderProgram);
    return shaderProgram;
    }
