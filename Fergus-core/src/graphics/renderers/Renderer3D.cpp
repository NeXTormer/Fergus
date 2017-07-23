#include "renderer3d.h"

Renderer3D::Renderer3D()
{
	glClearColor(1.0f, 0.4f, 0.0f, 1.0f);
}

void Renderer3D::prepare()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //already done by Window
}

void Renderer3D::render(RawModel* model)
{
	model->vao->bind();
	model->positionBuffer->bind();
	model->indexBuffer->bind();

	glDrawElements(GL_TRIANGLES, model->indexBuffer->getCount(), GL_UNSIGNED_SHORT, nullptr);
	
	model->positionBuffer->unbind();
	model->indexBuffer->unbind();
	model->vao->unbind();
}

void Renderer3D::render(TexturedModel* texturedModel)
{
	RawModel* model = texturedModel->getModel();

	model->vao->bind();
	model->positionBuffer->bind();
	model->indexBuffer->bind();

	glDrawElements(GL_TRIANGLES, model->indexBuffer->getCount(), GL_UNSIGNED_SHORT, nullptr);

	model->positionBuffer->unbind();
	model->indexBuffer->unbind();
	model->vao->unbind();
}
