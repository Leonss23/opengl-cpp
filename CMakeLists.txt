cmake_minimum_required(VERSION 3.27.0)
project(opengl_learning)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/glad.c
    src/opengl_wrapper/ShaderProgram.cpp
    src/opengl_wrapper/VBO.cpp
    src/opengl_wrapper/VAO.cpp
    src/opengl_wrapper/EBO.cpp
)

file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_directories(${PROJECT_NAME} PRIVATE lib)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 OpenGL::GL)
