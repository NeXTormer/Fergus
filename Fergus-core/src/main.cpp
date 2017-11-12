#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <algorithm>    // std::min

#include "fergus.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


//TODO: load shader in Mesh::draw

int main()
{
	Window window(960.0f, 540.0, "Lex ist lustig!");


	Camera camera(glm::vec3(0, 0, 0), window);

	Renderer3D renderer;
	

	GLfloat vertices [] = {
		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,0.5f,0,

		-0.5f,0.5f,1,
		-0.5f,-0.5f,1,
		0.5f,-0.5f,1,
		0.5f,0.5f,1,

		0.5f,0.5f,0,
		0.5f,-0.5f,0,
		0.5f,-0.5f,1,
		0.5f,0.5f,1,

		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		-0.5f,-0.5f,1,
		-0.5f,0.5f,1,

		-0.5f,0.5f,1,
		-0.5f,0.5f,0,
		0.5f,0.5f,0,
		0.5f,0.5f,1,

		-0.5f,-0.5f,1,
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,-0.5f,1

	};

	GLfloat textureCoords [] = {

		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0

	};

	GLushort indices [] = {
		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22

	};

	//RawModel model(vertices, 12 * 6, indices, 12 * 3, textureCoords, 23 * 2);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	//ModelTexture modelTexture("res/textures/basic2.png");
	//TexturedModel texturedModel(&model, &modelTexture);

	//Entity entity(&texturedModel, glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), 1);
	
	Model suit("res/models/bunny.obj");
	

	while (!window.closed())
	{
		window.clear();
		
		camera.update();

		shader.enable();

		// view/projection transformations
		
		glm::mat4 projection = glm::perspective(90.0f, 16.0f / 9.0f, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();
		shader.setUniformMat4("pr_matrix", projection);
		shader.setUniformMat4("vw_matrix", view);

		// render the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0, -0.1, 0));
		model = glm::scale(model, glm::vec3(0.002, 0.002, 0.002));
		model = glm::rotate(model, 100.f, glm::vec3(0, 1, 0));

		shader.setUniformMat4("ml_matrix", model);
		
		suit.draw(&shader);
		

		//entity.rotate(glm::vec3(0.01f, 0.01f, 0.0f));

		//renderer.render(&entity, &shader, &camera);

		window.update();
	}
	return 0;
}