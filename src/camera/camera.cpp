#include "camera.hpp"

namespace camera {
    Camera::Camera(
        float fov, float aspect, float z_near, float z_far, 
        glm::vec3 cam_pos, glm::vec3 up_vec, glm::vec3 cam_target) 
    : m_fov(fov), m_aspect(aspect), m_z_near(z_near), 
    m_z_far(z_far), m_cam_pos(cam_pos), m_up_vec(up_vec), 
    m_cam_target(cam_target) {}

    void Camera::set_cam_pos(glm::vec3 cam_pos) {
        m_cam_pos = cam_pos;
    }

    void Camera::set_up_vec(glm::vec3 up_vec) {
        m_up_vec = up_vec;
    }

    glm::mat4 Camera::get_view() {
        return glm::lookAt(
            m_cam_pos, 
            m_cam_target,
            m_up_vec
        );
    }

    glm::mat4 Camera::get_projection() {
        return glm::perspective(glm::radians(m_fov), m_aspect, m_z_near, m_z_far);
    }
}
