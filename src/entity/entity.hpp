#pragma once 
#include "glm/glm.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include <vector>
#include <string>

namespace entity {
    mesh::Mesh build_mesh(const std::vector<float> &vertices, 
        const std::vector<unsigned int> &indices);
    class Entity {
    public: 
        Entity(const std::vector<float> &vertices, 
            const std::string &vert_path, const std::string &frag_path, 
            const std::vector<unsigned int> &indices = {});
        glm::mat4 get_model();
        void rotate(float angle, const glm::vec3 &v);
        void translate(const glm::vec3 &v);
        void scale(const glm::vec3 &v);
        void draw();
        shader::Shader& get_shader();
    private: 
        mesh::Mesh m_mesh;
        glm::mat4 m_model;
        shader::Shader m_shader;
    };
}
