#pragma once
#include <GL\glew.h>
#include <iostream>

#include "macros.h"

static void fgClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static void fgLogError(const char* function, const char* file, int line)
{
	GLenum error;
	while (true)
	{
		error = glGetError();
		if (error == GL_NO_ERROR) return;

		std::cout << "[OpenGL Error] (" << error << ") at (" << function << ":" << line << " in " << file << std::endl;
	}
}