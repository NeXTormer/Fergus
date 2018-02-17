#pragma once

#include <GL\glew.h>

#include "../../utils/stb_image.h"


///Represents the texture of a model (diffusemap, normalmap, specularmap, ...)
class ModelTexture
{
public:
	ModelTexture(char* diffusePath);

	GLuint getDiffuseID();

	float shineDamper = 10;
	float reflectivity = 1;

private:
	GLuint diffuseID;

	GLuint generateTexture(char* path);
};