#pragma once

#include "../../maths/maths.h"

class Transformable
{
public:
	void move(const glm::vec3& d)
	{
		position += d;
		updateTransform();
	}
	void rotate(const glm::vec3& r) 
	{
		rotation += r;
		updateTransform();
	}
	void scale(const float s)
	{
		scaleFactor += s;
		updateTransform();
	}
	
	inline glm::vec3 getPosition() const { return position; }
	inline glm::vec3 getRotation() const { return rotation; }
	inline float getScale() const { return scaleFactor; }

	glm::mat4 getTransform()
	{
		return transformationmatrix;
	}

	void updateTransform()
	{
		glm::mat4 trmat;
		
		trmat = glm::scale(trmat, glm::vec3(scaleFactor));

		trmat = glm::rotate(trmat, rotation.x, glm::vec3(1, 0, 0));
		trmat = glm::rotate(trmat, rotation.y, glm::vec3(0, 1, 0));
		trmat = glm::rotate(trmat, rotation.z, glm::vec3(0, 0, 1));

		trmat = glm::translate(trmat, position);

		transformationmatrix = trmat;
	}


protected:
	Transformable(glm::vec3 pos, glm::vec3 rot, float sc)
		: position(pos), rotation(rot), scaleFactor(sc)
	{
		transformationmatrix = glm::scale(transformationmatrix, glm::vec3(scaleFactor));

		transformationmatrix = glm::rotate(transformationmatrix, rot.x, glm::vec3(1, 0, 0));
		transformationmatrix = glm::rotate(transformationmatrix, rot.y, glm::vec3(0, 1, 0));
		transformationmatrix = glm::rotate(transformationmatrix, rot.z, glm::vec3(0, 0, 1));
		
		transformationmatrix = glm::translate(transformationmatrix, position);
	}

	mat4 ml_matrix;

	glm::vec3 position;
	glm::vec3 rotation;

	glm::mat4 transformationmatrix;

	float rotationAngle;
	float scaleFactor;

};