#include "window.hpp"

namespace window {
    void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    Window::Window() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


        window = glfwCreateWindow(WITDH, HEIGHT, "Learn OpenGL", NULL, NULL);
        if (window == NULL) {
            std::cout << "Error Creating GLFW window" << std::endl;
            glfwTerminate();
            std::abort();
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to init GLAD" << std::endl;
            std::abort();
        }

        glViewport(0, 0, WITDH, HEIGHT);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    
    void Window::render(std::function<void(void)> callback) {
        while (!glfwWindowShouldClose(window)) {
            callback();
            inputHandler();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void Window::inputHandler() {
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}
