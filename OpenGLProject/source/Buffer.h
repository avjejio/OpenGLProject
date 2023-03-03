#pragma once

class Buffer {
public:
	Buffer(const void* data, unsigned int size, unsigned int type);
	~Buffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;
	unsigned int m_Type;
};