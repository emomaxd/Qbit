#include "IndexBuffer.hpp"


IndexBuffer::IndexBuffer(const GLuint* data, GLuint count) : count(count) {
	glGenBuffers(1, &m_programID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_programID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_programID);
}


void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_programID);
}

void IndexBuffer::UnBind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}