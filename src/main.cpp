#include "camera/camera.hpp"
#include "entity/entity.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "window.hpp"
#include "texture.hpp"
#include <cassert>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <utility>
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


    // from the book
    // too lazy for defining ebos for ts
    std::vector<float> light_vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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

    // Entity 
    std::vector<mesh::MeshData> house_data = {
        mesh::MeshData{
            .index = 0, 
            .size = 3
        },
        mesh::MeshData {
            .index = 1, 
            .size = 3,
        },
        mesh::MeshData {
            .index = 2, 
            .size = 2, 
        },
    };
    entity::Entity house = entity::Entity(vertices, "house_vert.glsl", "house_frag.glsl", house_data, indices);
    house.rotate(glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    std::vector<mesh::MeshData> light_cube_data = {
        mesh::MeshData{
            .index = 0,
            .size = 3,
        },
        mesh::MeshData{
            .index = 1, 
            .size = 3,
        },
    };

    std::vector<glm::vec3> positions = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
    };


    std::vector<std::pair<std::string, std::string>> cube_shaders = {
        {"light_vert.glsl", "light_frag.glsl"},
        {"ambient_vert.glsl", "ambient_frag.glsl"},
    };

    assert(cube_shaders.size() == positions.size());

    size_t num_cubes = positions.size();
    std::vector<entity::Entity> cubes; 

    for (size_t i = 0; i < num_cubes; i++) {

        auto [vert, frag] = cube_shaders[i];

        entity::Entity light_cube = entity::Entity(light_vertices, vert, frag, light_cube_data);
        light_cube.translate(positions[i]);
        cubes.push_back(std::move(light_cube));
    }


    // camera
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float k_aspect = 800.0f / 600.0f;
    glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cam_target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);

    camera::Camera cam(glm::radians(45.0f), k_aspect, 0.1f, 100.0f,
        cam_pos, up, cam_target, cam_front);

    const float radius = 10.0f;
    float camX, camZ;

    win.render([&]() {
        glClearColor(0.114f, 0.125f, 0.129f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto &house_shader = house.get_shader();
        house_shader.use();

        camX = sin(glfwGetTime()) * radius;
        camZ = cos(glfwGetTime()) * radius;
        //cam.set_cam_pos(glm::vec3(camX, 0.0f, camZ));
        auto view = cam.get_view();
        house_shader.set_uniform("view", view);

        auto model = house.get_model();
        house_shader.set_uniform("model", model);

        auto proj = cam.get_projection();
        house_shader.set_uniform("proj", proj);

        house_shader.set_uniform("texture1", 1);
        house_shader.set_uniform("texture2", 0);

        tex.bind();
        for (auto &cube : cubes) {
            auto &cube_shader = cube.get_shader();
            cube_shader.use();
            cube_shader.set_uniform("view", view);
            auto cube_model = cube.get_model();
            cube_shader.set_uniform("model", cube_model);
            cube_shader.set_uniform("proj", proj);

            cube_shader.set_uniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
            cube_shader.set_uniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
            cube.render();
        }

        house.render();


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

    });

    return 0;
}
