#pragma once
#include "GL\glew.h"
#include "../models/rawmodel.h"
#include "../models/texturedmodel.h"
#include "../models/modeltexture.h"
#include "../entities/entity.h"
#include "../shader.h"
#include "../camera.h"

class Renderer3D
{
public:
	Renderer3D();

	void prepare();
	void render(RawModel* model);
	void render(TexturedModel* model);
	void render(Entity* entity, Shader* shader, Camera* cam);

private:
	glm::mat4 projectionmatrix;
};