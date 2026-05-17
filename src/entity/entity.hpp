#pragma once 
#include "glm/glm.hpp"

#include "mesh.hpp"
#include <vector>

namespace entity {
    mesh::Mesh build_mesh(const std::vector<float> &vertices, 
        const std::vector<unsigned int> &indices);
    class Entity {
    public: 
        Entity(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
        glm::mat4 get_model();
        void rotate(float angle, const glm::vec3 &v);
        void translate(const glm::vec3 &v);
        void scale(const glm::vec3 &v);
        void draw();
    private: 
        mesh::Mesh m_mesh;
        glm::mat4 m_model;
    };
}
