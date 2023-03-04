#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "Shader.h"


#ifdef BUILD_RELEASE
#define GLCall(x) x;
#else 
#define ASSERT(x) if (!x) __debugbreak();
#define GLCall(x) GLClearErrors(); x; ASSERT(GLGetErrors(__FILE__, __LINE__));
#endif

void GLClearErrors();
bool GLGetErrors(const char* file, int line);


class Renderer {
public:
	void Draw(const VertexArray& vertexArray, const Buffer& indexBuffer, const Shader& shader) const;
	void Clear() const;
};