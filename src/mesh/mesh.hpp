#pragma once
#include "glad/glad.h"
#include <cstddef>
#include <optional>
#include <utility>

namespace mesh {
    class Mesh {
    public:
        Mesh(float *vertices, size_t vert_len, GLuint shape, std::optional<std::pair<unsigned int*, size_t>> ebo_pair);
        ~Mesh();

        void draw();

    private:
        GLuint VAO, VBO, EBO; 
        GLuint shape; 
        size_t indices_ebo;
    };

}
