#include "VertexArray.hpp"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &VAO);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &VAO);
}

void VertexArray::Bind() const {
	glBindVertexArray(VAO);
}

void VertexArray::UnBind() const {
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& VB, const VertexBufferLayout& layout) {
	
	Bind();
	VB.Bind();

	const auto& elements = layout.m_elements;
	
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); ++i) {

		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.m_stride, (const void*)offset );
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	
}
