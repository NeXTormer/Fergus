#pragma once

#include "../../fergus.h"

class Material
{
public:
	Material(Shader* shader, const char* texture, float shine = 15, float reflectivity = 1);
	~Material();

	inline int getDiffuseID();
	
	inline float getShineDamper();
	inline float getReflectivity();

	inline Shader* getShader();

private:
	GLuint loadTexture(const char* path);

	Shader* m_Shader;

	GLuint m_DiffuseID;
	
	float m_ShineDamper;
	float m_Reflectivity;
};

