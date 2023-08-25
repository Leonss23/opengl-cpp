#include "config.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int newShader(const char* shaderSource, GLenum shaderType);
unsigned int newShaderProgram(GLuint* shaders, uint16_t shaderCount);

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;

const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";

int main() {
    // GLFW Init
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
        }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW Window Init
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Learning OpenGL :D", NULL, NULL);

    if (window == NULL) {
        std::cout << "GLFW failed to create window" << std::endl;
        glfwTerminate();
        return -1;
        }

    // Proper window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLFW OpenGL Context Init
    glfwMakeContextCurrent(window);

    // GLAD Init
    gladLoadGL();

    // OpenGL Setup
    glViewport(0, 0, 1920, 1080);

    // Shaders
    unsigned int vertexShader = newShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = newShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    unsigned int shaders[] = { vertexShader, fragmentShader };

    // shader program
    unsigned int shaderProgram = newShaderProgram(shaders, sizeof(shaders) / sizeof(shaders[0]));

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up GL buffers
    GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
        };

    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        // logic
        processInput(window);

        // rendering
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // submit
        glfwSwapBuffers(window);
        glfwPollEvents();
        }

    // Clean Up OpenGL
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
    };

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    }

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        }
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

void handleProgramLinkError(unsigned int program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

GLuint newShader(const GLchar* shaderSource, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    handleShaderCompileError(shader);
    return shader;
    }

GLuint newShaderProgram(GLuint shaders[], uint16_t shaderCount) {
    GLuint shaderProgram = glCreateProgram();
    for (int i = 0; i < shaderCount; i++) {
        glAttachShader(shaderProgram, shaders[i]);
        }
    glLinkProgram(shaderProgram);
    handleProgramLinkError(shaderProgram);
    return shaderProgram;
    }