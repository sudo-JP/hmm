#include "mesh.hpp"

namespace mesh {
    Mesh::Mesh(float *vertices, size_t vert_len, GLuint shape, std::optional<std::pair<unsigned int*, size_t>> ebo_pair) : shape(shape) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        if (ebo_pair) {
            auto [indices, indices_len] = ebo_pair.value();
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_len, indices, GL_STATIC_DRAW);
            indices_ebo = indices_len;
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
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        if (EBO != 0) glDeleteBuffers(1, &EBO);
    }

    void Mesh::draw() {
        glBindVertexArray(VAO);
        if (EBO == 0) {
            glDrawArrays(shape, 0, 3);
        } else {
            glDrawElements(shape, indices_ebo, GL_UNSIGNED_INT, 0);
        }
    }
}
