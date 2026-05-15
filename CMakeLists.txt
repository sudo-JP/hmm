cmake_minimum_required(VERSION 3.8)
project(TestOpenGL VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(src/mesh)
add_subdirectory(src/shader)
add_subdirectory(src/window)
add_subdirectory(src/texture)

add_executable(TestOpenGL
    src/main.cpp
    src/glad.c
)

target_include_directories(TestOpenGL PRIVATE include)

target_link_libraries(TestOpenGL PRIVATE OpenGL::GL)
target_link_libraries(TestOpenGL PRIVATE mesh)
target_link_libraries(TestOpenGL PRIVATE window)
target_link_libraries(TestOpenGL PRIVATE shader)
target_link_libraries(TestOpenGL PRIVATE glfw)
target_link_libraries(TestOpenGL PRIVATE texture)

