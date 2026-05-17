#include "camera/camera.hpp"
#include "entity/entity.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "window.hpp"
#include "texture.hpp"
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <vector>
#define SPEED 0.05f

int main() {
    std::vector<float> vertices = {
        // Positions         // colors          // texures
        -0.5f, 0.0f, 0.0f,   1.0f, 0.5f, 0.0f,  0.0f, 0.5f,  // left top
        0.5f, 0.0f, 0.0f,    0.0f, 1.0f, 0.5f,  1.0f, 0.5f,  // right top
        0.0f, -0.5f, 0.0f,   0.5f, 1.0f, 0.0f,  0.5f, 0.5f,  // bottom middle 
        0.0f, 0.5f, 0.0f,    0.5f, 0.5f, 1.0f,  0.5f, 1.0f,  // roof 
        -0.5f, -0.5f, 0.0f,  0.5f, 0.0f, 0.0f,  0.0f, 0.0f,  // left bottom 
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  // right bottom 
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 1, 3,
        0, 4, 2,
        1, 2, 5,
    };

    // stuff
    window::Window win;
    texture::Texture tex("modiface.png", "tamm-cat.png");
    shader::Shader shader("vertex.glsl", "fragment.glsl");

    // Entity 
    entity::Entity house = entity::Entity(vertices, indices);
    house.rotate(glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // camera
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float k_aspect = 800.0f / 600.0f;
    glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cam_target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);

    camera::Camera cam(glm::radians(45.0f), k_aspect, 0.1f, 100.0f,
        cam_pos, up, cam_target, cam_front);

    const float radius = 10.0f;
    float camX, camZ;

    win.render([&]() {
        glClearColor(0.616f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();

        camX = sin(glfwGetTime()) * radius;
        camZ = cos(glfwGetTime()) * radius;
        //cam.set_cam_pos(glm::vec3(camX, 0.0f, camZ));
        auto view = cam.get_view();
        shader.set_uniform("view", view);

        auto model = house.get_model();
        shader.set_uniform("model", model);

        auto proj = cam.get_projection();
        shader.set_uniform("proj", proj);

        shader.set_uniform("texture1", 1);
        shader.set_uniform("texture2", 0);

        auto cam_pos = cam.get_cam_pos();
        auto cam_front = cam.get_cam_front();
        if (win.is_key_pressed(GLFW_KEY_W)) {
            cam.set_cam_pos(cam_pos + SPEED * cam_front);
        }
        if (win.is_key_pressed(GLFW_KEY_S)) {
            cam.set_cam_pos(cam_pos - SPEED * cam_front);
        }
        if (win.is_key_pressed(GLFW_KEY_A)) {
            cam.set_cam_pos(cam_pos - SPEED * glm::normalize(glm::cross(cam_front, up)));
        }
        if (win.is_key_pressed(GLFW_KEY_D)) {
            cam.set_cam_pos(cam_pos + SPEED * glm::normalize(glm::cross(cam_front, up)));
        }

        tex.bind();
        house.draw();
    });

    return 0;
}
