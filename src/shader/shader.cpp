#include "shader.hpp"
#include <cmath>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace shader {
    Shader::Shader(const std::string &vert_path, const std::string &frag_path) {
        const char *vertex; 
        auto vertexSource = retrieve_source_code("vertex.glsl");
        if (vertexSource) {
            vertex = vertexSource->c_str();
        } else {
            std::abort();
        }

        GLuint vertexShader; 
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertex, NULL);
        glCompileShader(vertexShader);
        GLint success = error_check_compile(vertexShader);
        if (!success) std::abort();


        auto fragSource = retrieve_source_code("fragment.glsl");
        const char *frag;
        if (fragSource) {
            frag = fragSource->c_str();
        } else {
            std::abort();
        }

        GLuint fragmentShader; 
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &frag, NULL);

        glCompileShader(fragmentShader);


        m_progID = glCreateProgram();

        glAttachShader(m_progID, vertexShader);
        glAttachShader(m_progID, fragmentShader);
        glLinkProgram(m_progID);


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }


    void Shader::use() {
        /*GLuint uniID = glGetUniformLocation(m_progID, "color");
        float time = glfwGetTime();
        glUniform4f(uniID, 0.5f, (sin(time) / 2.0f) + 0.5f, (cos(time) / 2.0f) + 0.5f, 1.0f);*/
        glUseProgram(m_progID);
        glUniform1i(glGetUniformLocation(m_progID, "texture1"), 1);
        glUniform1i(glGetUniformLocation(m_progID, "texture2"), 0);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view; 
        //= glm::mat4(1.0f);
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 proj = glm::mat4(1.0f);
        proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        const float radius = 5.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;

        glm::vec3 cameraPos = glm::vec3(camX, 0.0f, camZ);
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        //glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        //glm::vec3 cameraUp = glm::normalize(glm::cross(cameraRight, cameraDirection));


        view = glm::lookAt(
            cameraPos, 
            cameraTarget,
            up
        );

        unsigned int transformLoc = glGetUniformLocation(m_progID, "transform");
        unsigned int modelLoc = glGetUniformLocation(m_progID, "model");
        unsigned int viewLoc = glGetUniformLocation(m_progID, "view");
        unsigned int projLoc = glGetUniformLocation(m_progID, "proj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
    }

    void Shader::set_uniform(const char *attr, int val) {
        unsigned int loc = glGetUniformLocation(m_progID, attr);
        glUniform1i(loc, val);
    }
    void Shader::set_uniform(const char *attr, float val) {
        unsigned int loc = glGetUniformLocation(m_progID, attr);
        glUniform1f(loc, val);
    }
    void Shader::set_uniform(const char *attr, const glm::mat4 &val) {
        unsigned int loc = glGetUniformLocation(m_progID, attr);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
    }

    std::optional<std::string> Shader::retrieve_source_code(const std::string &path) {
        std::ifstream file(std::string(SHADER_DIR) + "/" + path);
        if (file.is_open()) {
            std::stringstream buffer; 
            buffer << file.rdbuf();
            return buffer.str();
        } else {
            std::cout << "Could not find file " << path << std::endl;
            return std::nullopt;
        }
    }

    GLint Shader::error_check_compile(GLuint gl_value) {
        GLint success; 
        char infoLog[512]; 
        glGetShaderiv(gl_value, GL_COMPILE_STATUS, &success); 
        if (!success) {
            glGetShaderInfoLog(gl_value, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        return success;
    }


    Shader::~Shader() {
        glDeleteProgram(m_progID);
    }
}
