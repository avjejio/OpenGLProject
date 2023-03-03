#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <string>
#include <fstream>


namespace GLProgram {
    static unsigned int CreateShader(int type, const char* src, const char* compileErMsg) {
        unsigned int shader = glCreateShader(type);

        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled == GL_FALSE) {
            char msg[1024];
            int length = 0;
            glGetShaderInfoLog(shader, 1024, &length, msg);
            printf("%s\n%s\n", compileErMsg, msg);
            return NULL;
        }
        return shader;
    }

    static std::string ReadFromFile(const char* path) {
        std::ifstream stream(path);
        std::string line;
        std::string out;
        while (std::getline(stream, line)) {
            out += line;
            out += '\n';
        }
        stream.close();

        return out;
    }

    unsigned int CreateProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {
        unsigned int program = glCreateProgram();

        std::string vertexShaderContent = ReadFromFile(vertexShaderPath);
        std::string fragmentShaderContent = ReadFromFile(fragmentShaderPath);

        unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderContent.c_str(), "Vertex shader failed to compile");
        unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderContent.c_str(), "Fragment shader failed to compile");

        //delete[] vertexShaderContent;
        //delete[] fragmentShaderContent;

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        int programLinked;
        glGetProgramiv(program, GL_LINK_STATUS, &programLinked);
        if (programLinked == GL_FALSE) {
            char msg[1024];
            int length;
            glGetProgramInfoLog(program, 1024, &length, msg);
            printf("%s\n%s\n", "Program failed to link", msg);
            return NULL;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return program;
    }
}