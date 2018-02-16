#include "material.h"

Material::Material(Shader* shader, const char* path, float shine, float reflectivity)
	: m_Shader(shader), m_ShineDamper(shine), m_Reflectivity(reflectivity)
{
	m_DiffuseID = loadTexture(path);
}

Material::~Material()
{
}

inline int Material::getDiffuseID()
{
	return m_DiffuseID;
}

inline float Material::getShineDamper()
{
	return m_ShineDamper;
}

inline float Material::getReflectivity()
{
	return m_Reflectivity;
}

inline Shader * Material::getShader()
{
	return m_Shader;
}

GLuint Material::loadTexture(const char* path)
{
	unsigned char* data;
	int width;
	int height;
	int nrChannels;

	data = stbi_load(path, &width, &height, &nrChannels, 0);
	GLuint id = 0;
	if (!data)
	{
		std::cout << "Failed to load image: " << path << std::endl;
		return 0;
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);

	return id;
}
