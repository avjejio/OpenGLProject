#include "Renderer.h"
#include "Buffer.h"

Buffer::Buffer(const void* data, unsigned int size, unsigned int type) : m_Type(type) {
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(m_Type, m_RendererID));
	GLCall(glBufferData(m_Type, size, data, GL_STATIC_DRAW));
}

Buffer::~Buffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void Buffer::Bind() const {
	GLCall(glBindBuffer(m_Type, m_RendererID));
}

void Buffer::Unbind() const {
	GLCall(glBindBuffer(m_Type, 0));
}