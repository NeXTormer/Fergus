#pragma once

#include <iostream>
#include <vector>
#include <GL\glew.h>

#include "../maths/maths.h"
#include "../utils/fileutils.h"

class Shader
{
private:
	GLuint m_ProgramID;
	const char* m_VertexPath;
	const char* m_FragmentPath;

	GLuint load();
	GLint getUniformLocation(const char* name);
public:
	Shader(const char* vertpath, const char* fragpath);
	~Shader();

	void enable();
	void disable();

	void setUniform1f(const char* name, float value);
	void setUniform2f(const char* name, float x, float y);
	void setUniform3f(const char* name, float x, float y, float z);
	void setUniform4f(const char* name, float x, float y, float z, float w);

	void setUniform2f(const char* name, const vec2 &value);
	void setUniform3f(const char* name, const vec3 &value);
	void setUniform4f(const char* name, const vec4 &value);

	void setUniform1i(const char* name, int value);
	void setUniformMat4(const char* name, const mat4 &matrix);




};