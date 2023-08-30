cmake_minimum_required(VERSION 3.27.0)
project(opengl_learning)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
src/main.cpp
src/window.cpp
src/utils.cpp
src/opengl_classes/ShaderProgram.cpp
src/opengl_classes/Shader.cpp
src/opengl_classes/VAO.cpp
src/opengl_classes/BufferObject.cpp
src/opengl_classes/Texture.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src/include)
target_include_directories(${PROJECT_NAME} PRIVATE src/include/opengl_classes)
target_include_directories(${PROJECT_NAME} PUBLIC lib)
target_include_directories(${PROJECT_NAME} PUBLIC lib/glfw/include)

# COPY RESOURCES (SHADERS) TO BUILD
add_custom_target(copy_resources ALL
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/res
${CMAKE_CURRENT_BINARY_DIR}/res
)

# LIBRARIES
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

add_library(glad
lib/glad/glad.h
lib/glad/glad.c
)

target_include_directories(glad PUBLIC lib)

add_library(
    stb
    lib/stb/stb_image.h
    lib/stb/stb_image.cpp
)

target_link_directories(${PROJECT_NAME} PRIVATE lib)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad stb glm)
