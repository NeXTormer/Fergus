#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "graphics\window.h"
#include "graphics\renderers\renderer3d.h"
#include "graphics\models\rawmodel.h"
#include "graphics\shader.h"
#include "graphics\models\modeltexture.h"
#include "graphics\models\texturedmodel.h"


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
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	ModelTexture modelTexture("res/textures/basic.png");
	TexturedModel texturedModel(&model, &modelTexture);
	

	while (!window.closed())
	{
		window.clear();
		shader.enable();
		renderer.render(&texturedModel);
		shader.disable();

		window.update();
	}
	return 0;
}