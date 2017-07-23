#pragma once

#include "rawmodel.h"
#include "modeltexture.h"

///Represents a RawModel with a ModelTexture applied to it.
class TexturedModel
{
public:
	TexturedModel(RawModel* model, ModelTexture* texture);

	RawModel* getModel();
	ModelTexture* getTexture();
private:
	RawModel* model;
	ModelTexture* texture;

};