#include "Renderer.h"
#include "VertexArray.h"

VertexArray::VertexArray() : m_IndexNext(0) {
	GLCall(glGenVertexArrays(1, &m_RendererID));
	//GLCall(glBindVertexArray(m_VertexArrayID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_RendererID))
}

void VertexArray::AddBufferLayout(const Buffer& buf, const BufferLayout& layout) {
	Bind();
	buf.Bind();

	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); ++i) {
		GLCall(glVertexAttribPointer(m_IndexNext, elements[i].count, elements[i].type, elements[i].normalized, layout.GetStride(), (const void*) elements[i].offset));
		GLCall(glEnableVertexAttribArray(m_IndexNext));
		++m_IndexNext;
	}
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}