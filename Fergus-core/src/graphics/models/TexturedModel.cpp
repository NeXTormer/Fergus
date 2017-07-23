#include "texturedmodel.h"

TexturedModel::TexturedModel(RawModel* model, ModelTexture* texture)
{
	this->model = model;
	this->texture = texture;
}

RawModel* TexturedModel::getModel()
{
	return model;
}

ModelTexture* TexturedModel::getTexture()
{
	return texture;
}
