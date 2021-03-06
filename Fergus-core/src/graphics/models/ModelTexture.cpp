#include "modeltexture.h"

#include <iostream>

ModelTexture::ModelTexture(char* diffusePath)
{
	diffuseID = generateTexture(diffusePath);
}

GLuint ModelTexture::getDiffuseID()
{
	return diffuseID;
}

GLuint ModelTexture::generateTexture(char* path)
{
	int width;
	int height;
	int nrChannels;
	unsigned char *data;

	data = stbi_load(path, &width, &height, &nrChannels, 3);
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

