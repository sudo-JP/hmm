#pragma once 
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>

namespace texture {
    class Texture {
    public: 
        Texture(const std::string &base, const std::string &overlay);
        ~Texture();
        void bind();

    private:
        GLuint m_texture1, m_texture2; 
    };
}
