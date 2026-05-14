#include "shader.hpp"

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
        success = errorCheckCompile(fragmentShader);
        if (!success) std::abort();


        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    void Shader::use() {
        glUseProgram(shaderProgram);
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
        glDeleteProgram(shaderProgram);
    }
}
