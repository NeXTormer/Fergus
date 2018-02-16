#pragma once

#include "../buffers/vertexarray.h"

///Represents a Model (vertices and indices) in 3D space
class RawModel
{
public:
	RawModel::RawModel(GLfloat* vertices, GLsizei verticesLength, GLfloat* normals, GLsizei normalsLength, GLushort* indices, GLsizei indicesLength, GLfloat* uv, GLsizei uvLength);

	~RawModel();
	
	VertexArray* vao;
	Buffer* positionBuffer;
	Buffer* uvBuffer;
	Buffer* normalsBuffer;
	IndexBuffer* indexBuffer;

	GLsizei getVertexCount();
private:
	GLsizei vertexCount;
	
};