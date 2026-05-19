#pragma once
#include "glad/glad.h"
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace mesh {
    struct MeshData {
        int index;
        int size; 
    };

    class Mesh {
    public:
        Mesh(const float *vertices, size_t vert_len, 
            GLuint shape, const std::vector<MeshData>&datas,
            std::optional<std::pair<const unsigned int*, size_t>> ebo_pair = std::nullopt);
        ~Mesh();
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        Mesh(Mesh&&other) noexcept;
        Mesh& operator=(Mesh&&other) noexcept;

        void draw();

    private:
        GLuint m_VAO = 0;
        GLuint m_VBO = 0;
        GLuint m_EBO = 0;
        GLuint m_shape = 0; 
        size_t m_indices_ebo = 0;
        size_t m_total_vertices = 0;
    };

}
