#include "renderer3d.h"

Renderer3D::Renderer3D()
{
	projectionmatrix = glm::perspective(90.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
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
	model->uvBuffer->bind();

	glBindTexture(GL_TEXTURE_2D, texturedModel->getTexture()->getDiffuseID());
	
	glDrawElements(GL_TRIANGLES, model->indexBuffer->getCount(), GL_UNSIGNED_SHORT, nullptr);

	model->positionBuffer->unbind();
	model->indexBuffer->unbind();
	model->uvBuffer->unbind();
	model->vao->unbind();
}

void Renderer3D::render(Entity* entity, Shader* shader, Camera* cam)
{
	TexturedModel* texturedModel = entity->getTexturedModel();
	RawModel* model = texturedModel->getModel();

	model->vao->bind();
	model->positionBuffer->bind();
	model->indexBuffer->bind();
	model->uvBuffer->bind();

	shader->enable();

	shader->setUniformMat4("ml_matrix", entity->getTransform());
	shader->setUniformMat4("pr_matrix", projectionmatrix);
	shader->setUniformMat4("vw_matrix", cam->getViewMatrix());

	glBindTexture(GL_TEXTURE_2D, texturedModel->getTexture()->getDiffuseID());

	glDrawElements(GL_TRIANGLES, model->indexBuffer->getCount(), GL_UNSIGNED_SHORT, nullptr);

	shader->disable();

	model->positionBuffer->unbind();
	model->indexBuffer->unbind();
	model->uvBuffer->unbind();
	model->vao->unbind();

}
