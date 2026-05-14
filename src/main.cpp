#include "shader.hpp"
#include "mesh.hpp"
#include "window.hpp"

int main() {
    float vertices[] = {
        -0.5f, 0.0f, 0.0f, 
        0.5f, 0.0f, 0.0f, 
        0.0f, -0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f, 
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 1, 3
    };
    std::pair<unsigned int*, size_t> p = {indices, 6};

    window::Window win;
    // 4 point, each with 3 vert
    mesh::Mesh mesh(vertices, 4 * 3, GL_TRIANGLES, p);
    shader::Shader shader("vertex.glsl", "fragment.glsl");

    win.render([&]() {
        shader.use();
        mesh.draw();
    });
    return 0;
}
