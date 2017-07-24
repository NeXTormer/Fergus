#pragma once

#include "../../maths/maths.h"
#include "../models/texturedmodel.h"

//TODO: split into renderable and transformable

class Entity
{
public:
	Entity(TexturedModel* model, vec3& position, const vec3& rotation, const float rotationangle, const float scale);

	void move(const vec3& d);
	void rotate(const vec3& axis);
	void scale(const float scale);

	TexturedModel* getTexturedModel();

	vec3 position;
	vec3 rotation;
	float rotationAngle;
	float scaleFactor;

private:
	TexturedModel* model;
};