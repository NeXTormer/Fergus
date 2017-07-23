#include "rawmodel.h"

RawModel::RawModel(GLfloat* vertices, GLsizei verticesLength, GLushort* indices, GLsizei indicesLength)
{
	vao = new VertexArray();
	positionBuffer = new Buffer(vertices, verticesLength, 3);
	indexBuffer = new IndexBuffer(indices, indicesLength);
	vao->bind();
	vao->addBuffer(positionBuffer, 0);
	vertexCount = indicesLength;
}

RawModel::~RawModel()
{
	//the vertexarray automatically deletes all associated buffers
	delete vao;
	delete indexBuffer;
}

GLsizei RawModel::getVertexCount()
{
	return vertexCount;
}
