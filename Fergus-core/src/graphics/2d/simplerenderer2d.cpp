#include "simplerenderer2d.h"

void SimpleRenderer2D::submit(const Renderable2D* renderable) 
{
	m_RenderQueue.push_back(renderable);
}

void SimpleRenderer2D::draw()
{
	while (!m_RenderQueue.empty())
	{
		const Renderable2D* renderable = m_RenderQueue.front();
		m_RenderQueue.pop_front();
		renderable->getVAO()->bind();
		renderable->getIBO()->bind();
		renderable->getShader().enable();

		glm::mat4 ml_matrix;
		glm::translate(ml_matrix, glm::vec3(renderable->getPosition().x, renderable->getPosition().y, renderable->getPosition().z));

		renderable->getShader().setUniformMat4("ml_matrix", ml_matrix);
		glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

		renderable->getIBO()->unbind();
		renderable->getVAO()->unbind();
	}
}