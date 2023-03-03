#pragma once

#include <vector>
#include "Renderer.h"

struct Elements {
	unsigned int type;
	int count;
	unsigned int normalized;
	unsigned int offset;
};

class BufferLayout {
public:
	BufferLayout() : m_Elements(), m_Stride(0) {}
	~BufferLayout() {}

	inline const std::vector<Elements>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }


	template <typename T>
	void Push(int count, unsigned int normalized){
		__debugbreak();
	}

	template<>
	void Push<float>(int count, unsigned int normalized) {
		m_Elements.push_back({ GL_FLOAT, count, normalized, m_Stride }); // Using stride as offset
		m_Stride += count * sizeof(float);
	}

private:
	std::vector<Elements> m_Elements;
	unsigned int m_Stride;
};