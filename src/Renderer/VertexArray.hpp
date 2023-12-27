#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include <GL/glew.h>


class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddBuffer(const VertexBuffer& VB, const VertexBufferLayout& layout);


private:
	GLuint VAO;
};