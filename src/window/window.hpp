#pragma once

#include "glad/glad.h"
#include <cstdlib>
#include "GLFW/glfw3.h"
#include <iostream>
#include <functional>


#define WITDH 800
#define HEIGHT 600
namespace window {
    class Window {
    public:
        Window();
        ~Window();
        void render(std::function<void(void)> callback);

    private:

        void inputHandler();
        GLFWwindow *window;
    };
}
