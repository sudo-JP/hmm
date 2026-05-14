#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <sstream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// Precondition: its under shader_dir path
std::optional<std::string> retrieveSourceCode(const std::string path) {
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

GLint errorCheckCompile(GLuint gl_value) {
    GLint success; 
    char infoLog[512]; 
    glGetShaderiv(gl_value, GL_COMPILE_STATUS, &success); 
    if (!success) {
        glGetShaderInfoLog(gl_value, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return success;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const int width = 800;
    const int height = 600;

    GLFWwindow *window = glfwCreateWindow(width, height, "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error Creating GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        -0.5f, 0.0f, 0.0f, 
        0.5f, 0.0f, 0.0f, 
        0.0f, -0.5f, 0.0f, 
        0.0f, 0.5f, 0.0f, 
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 1, 3
    };


    const char *vertex; 
    auto vertexSource = retrieveSourceCode("vertex.vert");
    if (vertexSource) {
        vertex = vertexSource->c_str();
    } else {
        return -1; 
    }

    GLuint vertexShader; 
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertex, NULL);
    glCompileShader(vertexShader);

    GLint success = errorCheckCompile(vertexShader);
    if (!success) return -1;

    auto fragSource = retrieveSourceCode("fragment.frag");
    const char *frag;
    if (fragSource) {
        frag = fragSource->c_str();
    } else {
        return -1; 
    }

    GLuint fragmentShader; 
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &frag, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram; 
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    success = errorCheckCompile(fragmentShader);
    if (!success) return -1; 


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLuint VAO, VBO, EBO; 

    glGenVertexArrays(1, &VAO);

    // 1 Object
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0; 
}
