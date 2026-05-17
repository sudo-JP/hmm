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
