#pragma once

#include <GL\glew.h>
#include <iostream>
#include <vector>

#include "buffer.h"
#include "indexbuffer.h"

class VertexArray
{
private:
	GLuint m_ArrayID;
	std::vector<Buffer*> m_Buffers;

public:
	VertexArray();
	~VertexArray();

	void addBuffer(Buffer* buffer, GLuint index);

	void bind() const;
	void unbind() const;
};