#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "graphics\window.h"
#include "graphics\3d\renderers\renderer3d.h"
#include "graphics\3d\rawmodel.h"
#include "graphics\shader.h"


int main(void)
{
	Window window(960.0f, 540.0, "Lex ist lustig!");

	Renderer3D renderer;
	

	GLfloat vertices[] = 
		{ -0.5f, 0.5f, 0, 
		-0.5f, -0.5f, 0, 
		0.5f, -0.5f, 0, 
		0.5f, 0.5f, 0 };
	GLushort indices[] = 
		{ 0, 1, 3, 
		3, 1, 2 };

	RawModel model(vertices, 18, indices, 6);
	Shader shader("src/shaders/3d/basic.vert", "src/shaders/3d/basic.frag");
	

	while (!window.closed())
	{
		window.clear();
		shader.enable();
		renderer.render(&model);
		shader.disable();

		window.update();
	}
	return 0;
}