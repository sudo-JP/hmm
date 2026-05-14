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

        glBufferData(GL_ARRAY_BUFFER, vert_len * sizeof(float), vertices, GL_STATIC_DRAW);

        // coordinate at 0 
        // each vertices has 3 point
        const int pos = 0;
        const int num_points_per_vert = 3;
        glVertexAttribPointer(pos, num_points_per_vert, GL_FLOAT, GL_FALSE, num_points_per_vert * sizeof(float), (void*)0);       
        glEnableVertexAttribArray(pos);

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
