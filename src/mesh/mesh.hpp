#pragma once
#include "glad/glad.h"
#include <cstddef>
#include <optional>
#include <utility>

namespace mesh {
    class Mesh {
    public:
        Mesh(const float *vertices, size_t vert_len, GLuint shape, std::optional<std::pair<const unsigned int*, size_t>> ebo_pair);
        ~Mesh();

        void draw();

    private:
        GLuint m_VAO, m_VBO, m_EBO, m_lightVAO; 
        GLuint m_shape; 
        size_t m_indices_ebo;
    };

}
