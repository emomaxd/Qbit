#pragma once
#include <vector>
#include <GL/glew.h>



struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {

		switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}

		return 0;
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout() : m_stride(0) {}

	template <typename T>
	void Push(unsigned int count) {
		//static_assert(false);
	}
	


	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
};

	template <>
	inline void VertexBufferLayout::Push<float>(unsigned int count) {
		m_elements.push_back(VertexBufferElement{ GL_FLOAT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}
	template <>
	inline void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
		m_elements.push_back(VertexBufferElement{ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}
	template <>
	inline void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
		m_elements.push_back(VertexBufferElement{ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}