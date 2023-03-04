#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Renderer.h"
#include "Shader.h"


Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) :
    m_RendererID(CompileShader(vertexShaderPath, fragmentShaderPath))
{
    Bind();
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int v) {
    GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocations.find(name) != m_UniformLocations.end()) {
        return m_UniformLocations.at(name);
    }

    int location;
    GLCall(location = glGetUniformLocation(m_RendererID, name.c_str()));

    if (location == -1) {
        std::cout << "Warning: Uniform '" << name << "' doesn't exist!\n";
    }

    m_UniformLocations[name] = location;

    return location;
}


std::string Shader::ReadFromFile(const std::string& path) {
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

unsigned int Shader::CreateShader(int type, const char* src, const char* compileErrMsg) {
    unsigned int shader;
    GLCall(shader = glCreateShader(type));

    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    int compiled;
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled));
    if (compiled == GL_FALSE) {
        char msg[1024];
        int length = 0;
        GLCall(glGetShaderInfoLog(shader, 1024, &length, msg));
        printf("%s\n%s\n", compileErrMsg, msg);
        return NULL;
    }
    return shader;
}

unsigned int Shader::CompileShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    unsigned int program = glCreateProgram();

    std::string vertexShaderContent = ReadFromFile(vertexShaderPath);
    std::string fragmentShaderContent = ReadFromFile(fragmentShaderPath);

    unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderContent.c_str(), "Vertex shader failed to compile");
    unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderContent.c_str(), "Fragment shader failed to compile");

    GLCall(glAttachShader(program, vertexShader));
    GLCall(glAttachShader(program, fragmentShader));
    GLCall(glLinkProgram(program));

    int programLinked;
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &programLinked));
    if (programLinked == GL_FALSE) {
        char msg[1024];
        int length;
        glGetProgramInfoLog(program, 1024, &length, msg);
        printf("%s\n%s\n", "Program failed to link", msg);
        return NULL;
    }

    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));
    return program;
}