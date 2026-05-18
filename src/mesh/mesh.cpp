#include "mesh.hpp"

namespace mesh {
    Mesh::Mesh(const float *vertices, size_t vert_len, GLuint shape, std::optional<std::pair<const unsigned int*, size_t>> ebo_pair) : m_shape(shape) {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);

        glGenVertexArrays(1, &m_lightVAO);
        glBindVertexArray(m_lightVAO);

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
        const int stride = 8;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);       
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));       
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));       
        glEnableVertexAttribArray(2);

        // Unbind VAO first to stop recording 
        glBindVertexArray(0);

        // Then unbind EBO and VBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Mesh::~Mesh() {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        if (m_EBO != 0) glDeleteBuffers(1, &m_EBO);
    }

    void Mesh::draw() {
        glBindVertexArray(m_VAO);
        if (m_EBO == 0) {
            glDrawArrays(m_shape, 0, 3);
        } else {
            glDrawElements(m_shape, m_indices_ebo, GL_UNSIGNED_INT, 0);
        }
    }
}
