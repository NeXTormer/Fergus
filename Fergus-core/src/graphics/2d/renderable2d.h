#pragma once

#include "..\buffers\vertexarray.h"
#include "..\buffers\indexbuffer.h"
#include "../../maths/maths.h"
#include "../shader.h"


class Renderable2D
{
public:
	Renderable2D(vec3 pos, vec2 size, vec4 color, Shader& shader)
		:m_Position(pos), m_Size(size), m_Color(color), m_Shader(shader)
	{
		m_VertexArray = new VertexArray();
		GLfloat vertices[] =
		{
			0, 0, 0,
			0, size.y, 0,
			size.x, size.y, 0,
			size.x, 0, 0
		};
		GLfloat colors[]
		{
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w,
			color.x, color.y, color.z, color.w
		};

		m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);


		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };

		m_IndexBuffer = new IndexBuffer(indices, 6);
	}
	virtual ~Renderable2D()
	{
		delete m_VertexArray;
		delete m_IndexBuffer;
	}

	inline const vec3& getPosition() const { return m_Position; }
	inline const vec2& getSize() const { return m_Size; }
	inline const vec4& getColor() const { return m_Color; }

	inline const VertexArray* getVAO() const { return m_VertexArray; }
	inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
	inline Shader& getShader() const { return m_Shader; }

protected:
	vec3 m_Position;
	vec2 m_Size;
	vec4 m_Color;

	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;
	Shader& m_Shader;
};