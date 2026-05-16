#include "shader.hpp"
#include "mesh.hpp"
#include "window.hpp"
#include "texture.hpp"
#include <iostream>

int main() {
    float vertices[] = {
        // Positions         // colors          // texures
        -0.5f, 0.0f, 0.0f,   1.0f, 0.5f, 0.0f,  0.0f, 0.0f,  
        0.5f, 0.0f, 0.0f,    0.0f, 1.0f, 0.5f,  0.5f, 0.5f, 
        0.0f, -0.5f, 0.0f,   0.5f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,    0.5f, 0.5f, 1.0f,  1.0f, 1.0f, 
        -0.5f, -0.5f, 0.0f,  0.5f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  0.5f, 0.0f, 
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3,
        0, 4, 2,
        1, 2, 5,
    };

    std::pair<unsigned int*, size_t> p = {indices, 12};
    window::Window win;

    texture::Texture tex("tamm-cat.png");
    mesh::Mesh mesh(vertices, sizeof(vertices), GL_TRIANGLES, p);
    shader::Shader shader("vertex.glsl", "fragment.glsl");

    win.render([&]() {
        glClearColor(0.616f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        tex.bind();
        mesh.draw();
    });

    return 0;
}
