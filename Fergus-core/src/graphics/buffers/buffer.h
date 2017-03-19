#pragma once

#include <GL\glew.h>

class Buffer
{
private:
	GLuint m_BufferID;
	GLuint m_ComponentSize; //size of one component in the array, eg. vec2 -> 2 components (x and y)

public:
	Buffer(GLfloat* data, GLsizei count , GLuint componentsize);

	void bind() const;
	void unbind() const;

	GLuint getComponentSize() const { return m_ComponentSize; }
};