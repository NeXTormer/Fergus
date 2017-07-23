#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <GL\glew.h>

#include "../utils/fileutils.h"
#include "../maths/maths.h"


class Shader
{
private:
	GLuint m_ProgramID;
	const char* m_VertexPath;
	const char* m_FragmentPath;

	GLuint load();
	GLint getUniformLocation(const GLchar* name) const;
public:
	Shader(const char* vertpath, const char* fragpath);
	~Shader();

	void enable();
	void disable();

	void setUniform1f(const GLchar* name, float value) const;
	void setUniform2f(const GLchar* name, float x, float y) const;
	void setUniform3f(const GLchar* name, float x, float y, float z) const;
	void setUniform4f(const GLchar* name, float x, float y, float z, float w) const;

	void setUniform2f(const GLchar* name, const vec2 &value) const;
	void setUniform3f(const GLchar* name, const vec3 &value) const;
	void setUniform4f(const GLchar* name, const vec4 &value) const ;

	void setUniform1i(const GLchar* name, int value) const;
	void setUniformMat4(const GLchar* name, const mat4 &matrix) const;




};