#include <iostream>
#include "Renderer.h"

void GLClearErrors() {
    while (glGetError());
}

bool GLGetErrors(const char* file, int line) {
    GLenum errorCode;
    std::string error;
    bool isOk = true;
    while (errorCode = glGetError()) {
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "GL_INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "GL_INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "GL_INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "GL_STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "GL_STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "GL_OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " | " << "(" << line << ")" << std::endl;
        isOk = false;
    }
    return isOk;
}

void Renderer::Draw(const VertexArray& vertexArray, const Buffer& indexBuffer, const Shader& shader) const {
    vertexArray.Bind();
    indexBuffer.Bind();
    shader.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}