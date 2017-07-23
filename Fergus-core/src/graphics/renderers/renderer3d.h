#pragma once
#include "GL\glew.h"
#include "../models/rawmodel.h"
#include "../models/texturedmodel.h"
#include "../models/modeltexture.h"

class Renderer3D
{
public:
	Renderer3D();

	void prepare();
	void render(RawModel* model);
	void render(TexturedModel* model);


private:

};