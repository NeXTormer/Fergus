#pragma once

#include "../buffers/vertexarray.h"

///Represents a Model (vertices and indices) in 3D space
class RawModel
{
public:
	RawModel(GLfloat* vertices, GLsizei vertCount, GLushort* indices, GLsizei indexCount, GLfloat* uv, GLsizei uvLength);

	~RawModel();
	
	VertexArray* vao;
	Buffer* positionBuffer;
	Buffer* uvBuffer;
	IndexBuffer* indexBuffer;

	GLsizei getVertexCount();
private:
	GLsizei vertexCount;
	
};