#pragma once

#include "Buffer.h"
#include "BufferLayout.h"

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void AddBufferLayout(const Buffer& buf, const BufferLayout& layout);

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
	unsigned int m_IndexNext;
};