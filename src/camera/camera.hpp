#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

namespace camera {
    class Camera {
    public:
        Camera(
            float fov, float aspect, float z_near, float z_far, 
            glm::vec3 cam_pos, glm::vec3 up_vec, glm::vec3 cam_target
        );
        ~Camera();
        glm::mat4 get_view();
        glm::mat4 get_projection();

        void set_cam_pos(glm::vec3 cam_pos);
        void set_up_vec(glm::vec3 up_vec);
    private:
        float m_fov, m_aspect, m_z_near, m_z_far;
        glm::vec3 m_cam_pos, m_up_vec, m_cam_target;
    };
}
