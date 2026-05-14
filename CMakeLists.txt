cmake_minimum_required(VERSION 3.8)
project(TestOpenGL VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

add_executable(TestOpenGL
    src/main.cpp
    src/glad.c
)

target_include_directories(TestOpenGL PRIVATE include)
target_compile_definitions(TestOpenGL PRIVATE SHADER_DIR="${CMAKE_SOURCE_DIR}/shaders")

target_link_libraries(TestOpenGL PRIVATE glfw)

