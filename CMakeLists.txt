cmake_minimum_required(VERSION 3.27.0)
project(opengl_learning)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/glad.c
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src/include)
target_link_directories(${PROJECT_NAME} PRIVATE lib)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
