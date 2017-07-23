#pragma once

#include "../buffers/vertexarray.h"
class RawModel
{
public:
	RawModel(GLfloat* vertices, GLsizei vertCount, GLushort* indices, GLsizei indexCount);
	~RawModel();

	VertexArray *vao;
	Buffer *positionBuffer;
	IndexBuffer* indexBuffer;

	GLsizei getVertexCount();
private:
	GLsizei vertexCount;
	
};