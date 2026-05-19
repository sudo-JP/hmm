#include "mesh.hpp"
#include <iostream>

namespace mesh {
    Mesh::Mesh(const float *vertices, size_t vert_len, GLuint shape, const std::vector<MeshData> &datas,
            std::optional<std::pair<const unsigned int*, size_t>> ebo_pair) : m_shape(shape) {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        if (ebo_pair) {
            auto [indices, indices_len] = ebo_pair.value();
            glGenBuffers(1, &m_EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_len, indices, GL_STATIC_DRAW);
            m_indices_ebo = indices_len;
        }

        glBufferData(GL_ARRAY_BUFFER, vert_len, vertices, GL_STATIC_DRAW);

        // coordinate at location 0, layout
        // each vertices has 3 point
        // Layout 0, 1, 2
        int stride = 0;
        for (const MeshData &data : datas) {
            stride += data.size;
        }

        int prefix_sum = 0;
        for (const MeshData &data: datas) {
            glVertexAttribPointer(
                data.index, 
                data.size, 
                GL_FLOAT, GL_FALSE, stride * sizeof(float), 
                (void*)(prefix_sum * sizeof(float))
            );
            glEnableVertexAttribArray(data.index);
            prefix_sum += data.size;
        }

        m_total_vertices = vert_len / sizeof(float) / stride;

        // Unbind VAO first to stop recording 
        glBindVertexArray(0);

        // Then unbind EBO and VBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Mesh::~Mesh() {
        if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO != 0) glDeleteBuffers(1, &m_VBO);
        if (m_EBO != 0) glDeleteBuffers(1, &m_EBO);
    }

    Mesh::Mesh(Mesh&&other) noexcept 
    : m_EBO(other.m_EBO), m_VAO(other.m_VAO), 
    m_VBO(other.m_VBO), m_indices_ebo(other.m_indices_ebo), 
    m_shape(other.m_shape), m_total_vertices(other.m_total_vertices) {
        other.m_EBO = 0;
        other.m_VAO = 0;
        other.m_VBO = 0;
        other.m_indices_ebo = 0;
        other.m_shape = 0;
        other.m_total_vertices = 0;
    }

    Mesh& Mesh::operator=(Mesh &&other) noexcept {
        if (this != &other) {
            m_EBO = other.m_EBO; 
            m_VAO = other.m_VAO; 
            m_VBO = other.m_VBO;
            m_indices_ebo = other.m_indices_ebo;
            m_shape = other.m_shape;
            m_total_vertices = other.m_total_vertices;

            other.m_EBO = 0;
            other.m_VAO = 0;
            other.m_VBO = 0;
            other.m_indices_ebo = 0;
            other.m_shape = 0;
            other.m_total_vertices = 0;
        }
        return *this;
    }

    void Mesh::draw() {
        glBindVertexArray(m_VAO);
        if (m_EBO == 0) {
            glDrawArrays(m_shape, 0, m_total_vertices);
        } else {
            glDrawElements(m_shape, m_indices_ebo, GL_UNSIGNED_INT, 0);
        }
    }
}
