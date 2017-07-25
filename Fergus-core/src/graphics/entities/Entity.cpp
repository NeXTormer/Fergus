#include "entity.h"

Entity::Entity(TexturedModel* model, glm::vec3& position, const glm::vec3& rotation, const float scale)
	: Transformable(position, rotation, scale)
{
	this->model = model;
}

TexturedModel * Entity::getTexturedModel()
{
	return model;
}

