#include "entity.hpp"
#include <optional>
#include <string>
#include <utility>
#include "glm/gtc/matrix_transform.hpp"

namespace entity {
    mesh::Mesh build_mesh(const std::vector<float> &vertices, 
            const std::vector<mesh::MeshData> &datas,
            const std::vector<unsigned int> &indices) {
        std::optional<std::pair<const unsigned int*, size_t>> ebo_param = std::nullopt;
        if (indices.size() > 0) {
            std::pair<const unsigned int*, size_t> p = {indices.data(), indices.size()};
            ebo_param = p;
        } 
        return mesh::Mesh(vertices.data(), vertices.size() * sizeof(float), GL_TRIANGLES, datas, ebo_param);
    }

    Entity::Entity(const std::vector<float> &vertices, 
        const std::string &vert_path, const std::string &frag_path, 
        const std::vector<mesh::MeshData> &datas,
        const std::vector<unsigned int> &indices)
        : m_mesh(build_mesh(vertices, datas, indices)), m_model(glm::mat4(1.0f)), m_shader(vert_path, frag_path) {}

    void Entity::render() { 
        m_shader.use();
        m_mesh.draw(); 
    }

    glm::mat4 Entity::get_model() { return m_model; }

    shader::Shader& Entity::get_shader() { return m_shader; }

    void Entity::rotate(float angle, const glm::vec3 &v) { 
        m_model = glm::rotate(m_model, angle, v);
    }


    void Entity::translate(const glm::vec3 &v) {
        m_model = glm::translate(m_model, v);
    }

    void Entity::scale(const glm::vec3 &v) {
        m_model = glm::scale(m_model, v);
    }
}
