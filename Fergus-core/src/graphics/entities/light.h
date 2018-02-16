#pragma once

#include "../../maths/maths.h"
#include "../entities/transformable.h"

class Light : public Transformable
{
private:
	glm::vec3 m_Color;
	glm::vec3 m_Attenuation;

public:
	Light(glm::vec3 pos, glm::vec3 color, glm::vec3 attenuation = glm::vec3(1, 1, 1))
		: Transformable(pos, glm::vec3(0, 0, 0), 1), m_Color(color), m_Attenuation(attenuation)
	{ }
	
	void setColor(glm::vec3 color)
	{
		m_Color = color;
	}

	void setAttenuation(glm::vec3 attenuation)
	{
		m_Attenuation = attenuation;
	}

	glm::vec3 getColor()
	{
		return m_Color;
	}

	glm::vec3 getAttenuation()
	{
		return m_Attenuation;
	}
};