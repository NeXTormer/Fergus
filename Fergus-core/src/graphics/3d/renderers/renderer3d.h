#pragma once
#include "GL\glew.h"
#include "../rawmodel.h"

class Renderer3D
{
public:
	Renderer3D();

	void prepare();
	void render(RawModel* model);


private:

};