#pragma once
#include <GL/glew.h>

class IndexBuffer {
public:
	IndexBuffer(const GLuint* data, GLuint count);
	~IndexBuffer();
	void Bind() const;
	void UnBind() const;

	inline GLuint getCount() const { return count; }

private:
	GLuint m_programID;
	GLuint count;
};