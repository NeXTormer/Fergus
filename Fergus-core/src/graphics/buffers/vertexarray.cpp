#include "vertexarray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ArrayID);
}

VertexArray::~VertexArray()
{
	for (int i = 0; i < m_Buffers.size(); i++)
	{
		delete m_Buffers[i];
	}
}

void VertexArray::addBuffer(Buffer* buffer, GLuint index)
{
	bind();
	buffer->bind();

	glEnableVertexAttribArray(index);

	//index, component size, type, normalized, dist btw objects, offset
	glVertexAttribPointer(index, buffer->getComponentSize(), GL_FLOAT, GL_FALSE, 0, 0);

	//add to vector

	buffer->unbind();
	unbind();
}

void VertexArray::bind() const
{
	glBindVertexArray(m_ArrayID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}