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
#include "loaders\objloader.h"

#include "graphics\entities\light.h"


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

	RawModel dragonModel = OBJLoader::TestLoadObj("res/models/cube.obj");

	Shader shader("src/shaders/3d/onlytexture.vert", "src/shaders/3d/onlytexture.frag");
	ModelTexture dragonTexture("res/textures/default2.png");

	TexturedModel dragonTexturedModel(&dragonModel, &dragonTexture);

	Entity dragon(&dragonTexturedModel, glm::vec3(0, 0, -4), glm::vec3(0, 0, 0), 1);
	
	Light light(glm::vec3(0, 3, 15), glm::vec3(0.5, 0.5, 0.5));

	shader.enable();
	//shader.setUniform3f("lightColor", light.getColor());
	//shader.setUniform3f("lightPosition", light.getPosition());
	//shader.setUniform1f("shineDamper", dragonTexture.shineDamper);
	//shader.setUniform1f("reflectivity", dragonTexture.reflectivity);


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
		
		

		dragon.rotate(glm::vec3(0.01f, 0.013f, 0.01f));

		//renderer.render(&dragonModel);
		renderer.render(&dragon, &shader, &camera);

		window.update();
	}
	return 0;
}