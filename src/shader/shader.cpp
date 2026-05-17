#include "shader.hpp"
#include <glm/trigonometric.hpp>

namespace shader {
    Shader::Shader(const std::string &vert_path, const std::string &frag_path) {
        const char *vertex; 
        auto vertexSource = retrieveSourceCode("vertex.glsl");
        if (vertexSource) {
            vertex = vertexSource->c_str();
        } else {
            std::abort();
        }

        GLuint vertexShader; 
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertex, NULL);
        glCompileShader(vertexShader);
        GLint success = errorCheckCompile(vertexShader);
        if (!success) std::abort();


        auto fragSource = retrieveSourceCode("fragment.glsl");
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


        progID = glCreateProgram();

        glAttachShader(progID, vertexShader);
        glAttachShader(progID, fragmentShader);
        glLinkProgram(progID);


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }


    void Shader::use() {
        /*GLuint uniID = glGetUniformLocation(progID, "color");
        float time = glfwGetTime();
        glUniform4f(uniID, 0.5f, (sin(time) / 2.0f) + 0.5f, (cos(time) / 2.0f) + 0.5f, 1.0f);*/
        glUseProgram(progID);
        glUniform1i(glGetUniformLocation(progID, "texture1"), 1);
        glUniform1i(glGetUniformLocation(progID, "texture2"), 0);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 proj = glm::mat4(1.0f);
        proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        unsigned int transformLoc = glGetUniformLocation(progID, "transform");
        unsigned int modelLoc = glGetUniformLocation(progID, "model");
        unsigned int viewLoc = glGetUniformLocation(progID, "view");
        unsigned int projLoc = glGetUniformLocation(progID, "proj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
    }

    std::optional<std::string> Shader::retrieveSourceCode(const std::string path) {
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

    GLint Shader::errorCheckCompile(GLuint gl_value) {
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
        glDeleteProgram(progID);
    }
}
