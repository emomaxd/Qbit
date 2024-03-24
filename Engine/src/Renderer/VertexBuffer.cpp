#include "VertexBuffer.hpp"


VertexBuffer::VertexBuffer(const void* data, GLuint size) {
	glGenBuffers(1, &m_programID);
	glBindBuffer(GL_ARRAY_BUFFER, m_programID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_programID);
}


void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_programID);
}

void VertexBuffer::UnBind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}