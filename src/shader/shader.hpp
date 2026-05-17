#pragma once 
#include "glad/glad.h"
#include <optional>
#include <string>
#include "glm/glm.hpp"

namespace shader {
    class Shader {
    public:
        Shader(const std::string &vert_path, const std::string &frag_path);
        ~Shader();
        void use();
        void set_uniform(const char *attr, int val);
        void set_uniform(const char *attr, float val);
        void set_uniform(const char *attr, const glm::mat4 &val);

    private:
        std::optional<std::string> retrieve_source_code(const std::string &path);
        GLint error_check_compile(GLuint gl_value);
        GLuint m_progID; 
    };
}
