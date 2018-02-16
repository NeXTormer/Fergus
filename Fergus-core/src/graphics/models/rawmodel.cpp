#include "rawmodel.h"

RawModel::RawModel(GLfloat* vertices, GLsizei verticesLength, GLfloat* normals, GLsizei normalsLength, GLushort* indices, GLsizei indicesLength, GLfloat* uv, GLsizei uvLength)
{
	vao = new VertexArray();
	positionBuffer = new Buffer(vertices, verticesLength, 3);
	indexBuffer = new IndexBuffer(indices, indicesLength);
	uvBuffer = new Buffer(uv, uvLength, 2);
	normalsBuffer = new Buffer(normals, normalsLength, 3);
	vao->bind();
	vao->addBuffer(positionBuffer, 0);
	vao->addBuffer(uvBuffer, 1);
	vao->addBuffer(normalsBuffer, 2);
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
