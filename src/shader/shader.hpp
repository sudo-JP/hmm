#pragma once 
#include "glad/glad.h"
#include <optional>
#include <string>

namespace shader {
    class Shader {
    public:
        Shader(const std::string &vert_path, const std::string &frag_path);
        ~Shader();
        void use();

    private:
        std::optional<std::string> retrieveSourceCode(const std::string path);
        GLint errorCheckCompile(GLuint gl_value);
        GLuint progID; 
    };
}
