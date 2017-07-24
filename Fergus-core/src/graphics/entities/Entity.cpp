#include "entity.h"

Entity::Entity(TexturedModel* model, vec3& position, const vec3& rotation, const float rotationangle, const float scale)
	: position(position), rotation(rotation), scaleFactor(scale) 
{
	this->model = model;
}

void Entity::move(const vec3& d)
{
	position += d;
}

void Entity::rotate(const vec3& r)
{
	rotation += r;
}

void Entity::scale(const float scale)
{
	scaleFactor += scale;
}

TexturedModel * Entity::getTexturedModel()
{
	return model;
}

