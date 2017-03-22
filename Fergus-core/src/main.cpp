#include <iostream>
#include <string>

#include "graphics\window.h"
#include "graphics\shader.h"
#include "maths\maths.h"
#include "utils\fileutils.h"
#include "graphics\buffers\buffer.h"
#include "graphics\buffers\indexbuffer.h"
#include "graphics\buffers\vertexarray.h"
#include "graphics\renderable2d.h"
#include "graphics\simplerenderer2d.h"



int main(void)
{
	Window window(960.0f, 540.0, "Lex ist lustig!");
	glClearColor(0.6, 1, 0.5, 1);
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	Renderable2D sprite(vec3(5, 5, 0), vec2(4, 4), vec4(1, 0.5f, 0.05f, 1), shader);
	Renderable2D sprite2(vec3(7, 1, 0), vec2(2, 3), vec4(0.2f, 0.5f, 1, 1), shader);
	SimpleRenderer2D renderer;

	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		double x = window.getMouseX();
		double y = window.getMouseY();
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.draw();

		window.update();
	}
	return 0;
}