#pragma once

#include "../../maths/maths.h"
#include "../models/texturedmodel.h"
#include "transformable.h"

//TODO: split into renderable and transformable

class Entity : public Transformable
{
public:
	Entity(TexturedModel* model, glm::vec3& position, const glm::vec3& rotation, const float scale);

	
	
	TexturedModel* getTexturedModel();

	

private:
	TexturedModel* model;
};