#pragma once

#include <GL\glew.h>

#include "../../utils/stb_image.h"


///Represents the texture of a model (diffusemap, normalmap, specularmap, ...)
class ModelTexture
{
public:
	ModelTexture(char* diffusePath);

	GLuint getDiffuseID();

private:
	GLuint diffuseID;
	int width;
	int height;
	int nrChannels;
	unsigned char *data;

	GLuint generateTexture(char* path);
};