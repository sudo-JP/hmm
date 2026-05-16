#pragma once 
#include "glad/glad.h"
#include <optional>
#include <string>
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
