#pragma once

#include <GL\glew.h>

#include "../../maths/maths.h"
#include "renderable2d.h"

class Renderer2D
{
public:
	virtual void submit(const Renderable2D* renderable) = 0;
	virtual void draw() = 0;
};