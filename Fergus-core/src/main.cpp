#include <iostream>
#include <string>

#include "graphics\window.h"
#include "graphics\shader.h"
#include "maths\maths.h"
#include "utils\fileutils.h"
#include "graphics\buffers\buffer.h"
#include "graphics\buffers\indexbuffer.h"
#include "graphics\buffers\vertexarray.h"



int main(void)
{
	Window window(800, 600, "Lex ist lustig!");
	glClearColor(0.6, 1, 0.5, 1);

	

#if 0
	GLfloat vertices[] =
	{
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
#else
	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};

	GLushort indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	GLfloat colorsA[] =
	{
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1
	};

	GLfloat colorsB[] =
	{
		0.8f, 0.1f, 0.4f, 1,
		0.8f, 0.1f, 0.4f, 1,
		0.8f, 0.1f, 0.4f, 1,
		0.8f, 0.1f, 0.4f, 1
	};

	VertexArray vao1;
	VertexArray vao2;
	IndexBuffer ibo(indices, 6);
	vao1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	vao1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);
	vao2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	vao2.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);



#endif

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
	

	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
	while (!window.closed())
	{
		window.clear();
		
		shader.setUniform2f("light_pos", vec2((float)(window.getMouseX() * 16.0f / 800), (float)(9.0f - window.getMouseY() * 9.0f / 600)));
#if 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
#else
		vao1.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

		vao2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
#endif
		window.update();
	}

	return 0;
}