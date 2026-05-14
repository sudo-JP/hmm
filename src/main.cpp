#include "shader.hpp"
#include "mesh.hpp"
#include "window.hpp"
#include <iostream>

int main() {
    float vertices[] = {
        -0.5f, 0.0f, 0.0f, 
        0.5f, 0.0f, 0.0f, 
        0.0f, -0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3,
        0, 4, 2,
        1, 2, 5,
    };

    std::pair<unsigned int*, size_t> p = {indices, 12};
    window::Window win;

    // 4 point, each with 3 vert
    mesh::Mesh mesh(vertices, 6 * 3, GL_TRIANGLES, p);
    shader::Shader shader("vertex.glsl", "fragment.glsl");

    win.render([&]() {
        glClearColor(0.616f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        mesh.draw();
    });

    return 0;
}
