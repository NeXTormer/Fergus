#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "graphics\window.h"
#include "graphics\camera.h"
#include "graphics\renderers\renderer3d.h"
#include "graphics\models\rawmodel.h"
#include "graphics\shader.h"
#include "graphics\models\modeltexture.h"
#include "graphics\models\texturedmodel.h"
#include "graphics\entities\entity.h"


int main()
{
	Window window(960.0f, 540.0, "Lex ist lustig!");

	Camera camera(glm::vec3(0, 0, 0), window);



	Renderer3D renderer;
	

	GLfloat vertices[] = 
	{ 
		-0.5f,  0.5f, 0, 
		-0.5f, -0.5f, 0, 
		 0.5f, -0.5f, 0, 
		 0.5f,  0.5f, 0
	};
	GLushort indices[] = 
	{
		0, 1, 3, 
		3, 1, 2 
	};
	GLfloat texturecoords[] = 
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f, 
		1.0f, 0.0f
	};

	RawModel model(vertices, 18, indices, 6, texturecoords, 8);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	ModelTexture modelTexture("res/textures/basic2.png");
	TexturedModel texturedModel(&model, &modelTexture);

	Entity entity(&texturedModel, glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), 1);
	

	while (!window.closed())
	{
		window.clear();
		
		camera.update();
		renderer.render(&entity, &shader, &camera);

		window.update();
	}
	return 0;
}