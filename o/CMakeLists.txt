cmake_minimum_required(VERSION 3.24)

project(hmm VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
    GIT_SHALLOW ON
)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW ON
)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(glm glfw stb)

find_program(GLAD_EXECUTABLE glad REQUIRED)

set(GLAD_OUTPUT_DIR "${CMAKE_BINARY_DIR}/glad")

add_custom_command(
    OUTPUT
        "${GLAD_OUTPUT_DIR}/include/glad/gl.h"
        "${GLAD_OUTPUT_DIR}/include/KHR/khrplatform.h"
        "${GLAD_OUTPUT_DIR}/src/gl.c"
    COMMAND
        ${CMAKE_COMMAND} -E make_directory
        "${GLAD_OUTPUT_DIR}"
    COMMAND
        ${GLAD_EXECUTABLE}
        --api gl:core=4.6
        --out-path "${GLAD_OUTPUT_DIR}"
        --reproducible
    COMMENT "Generating GLAD OpenGL 4.6 loader"
)

add_custom_target(glad_generate
    DEPENDS
        "${GLAD_OUTPUT_DIR}/include/glad/gl.h"
        "${GLAD_OUTPUT_DIR}/include/KHR/khrplatform.h"
        "${GLAD_OUTPUT_DIR}/src/gl.c"
)


add_library(glad_gl STATIC
    "${GLAD_OUTPUT_DIR}/src/gl.c"
)

add_dependencies(glad_gl glad_generate)

target_include_directories(glad_gl PUBLIC
    "${GLAD_OUTPUT_DIR}/include"
)

find_package(OpenGL REQUIRED)

add_executable(hmm
    src/main.cpp
    src/camera/camera.cpp
    src/camera/camera.hpp
    src/entity/entity.cpp
    src/entity/entity.hpp
    src/mesh/mesh.cpp
    src/mesh/mesh.hpp
    src/shader/shader.cpp
    src/shader/shader.hpp
    src/texture/texture.cpp
    src/texture/texture.hpp
    src/window/window.cpp
    src/window/window.hpp
)

target_include_directories(hmm PRIVATE
    src
    "${stb_SOURCE_DIR}"
)

target_compile_definitions(hmm PRIVATE
    "IMAGE_DIR=\"${CMAKE_SOURCE_DIR}/src/texture\""
    "SHADER_DIR=\"${CMAKE_SOURCE_DIR}/src/shader/shading\""
)

target_link_libraries(hmm PRIVATE
    glad_gl
    glfw
    glm::glm
    OpenGL::GL
)
