cmake_minimum_required(VERSION 3.27.0)
project(opengl_learning)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME}
    lib/glad/glad.c
    src/main.cpp
    src/window.cpp
    src/utils.cpp
    src/opengl_classes/ShaderProgram.cpp
    src/opengl_classes/Shader.cpp
    src/opengl_classes/VAO.cpp
    src/opengl_classes/BufferObject.cpp
)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${CMAKE_CURRENT_BINARY_DIR}/res
    )

target_include_directories(${PROJECT_NAME} PRIVATE src/include)
target_include_directories(${PROJECT_NAME} PRIVATE src/include/opengl_classes)
target_include_directories(${PROJECT_NAME} PRIVATE lib)
target_include_directories(${PROJECT_NAME} PRIVATE lib/glfw/include)
target_link_directories(${PROJECT_NAME} PRIVATE lib)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
