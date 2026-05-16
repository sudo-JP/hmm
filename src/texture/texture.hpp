#pragma once 
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>

namespace texture {
    class Texture {
    public: 
        Texture(const std::string &file_name);
        ~Texture();
        void bind();

    private:
        GLuint texture; 
    };
}
