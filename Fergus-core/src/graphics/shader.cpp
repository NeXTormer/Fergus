#include "shader.h"

Shader::Shader(const char* vertpath, const char* fragpath)
	: m_VertexPath(vertpath), m_FragmentPath(fragpath)
{
	m_ProgramID = load();
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
}

void Shader::enable()
{
	glUseProgram(m_ProgramID);
}

void Shader::disable()
{
	glUseProgram(0);
}

GLuint Shader::load()
{
	GLint result;

	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexSourceString = FileUtils::read_file(m_VertexPath);
	std::string fragmentSourceString = FileUtils::read_file(m_FragmentPath);

	const char* vertexSource = vertexSourceString.c_str();
	const char* fragmentSource = fragmentSourceString.c_str();

	//Vertex Shader
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
		glDeleteShader(vertex);
		return 0;
	}

	//Fragment Shader
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
		glDeleteShader(fragment);
		return 0;
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

GLint Shader::getUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(m_ProgramID, name);
}

void Shader::setUniform1f(const GLchar* name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform1i(const GLchar* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform2f(const GLchar* name, const vec2& vector)
{
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void Shader::setUniform3f(const GLchar* name, const vec3& vector)
{
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::setUniform4f(const GLchar* name, const vec4& vector)
{
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniformMat4(const GLchar* name, const mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
}