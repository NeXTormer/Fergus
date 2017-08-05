#pragma once

#include <GL\glew.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../glm/glm.hpp"
#include "../shader.h"
#include "../buffers/vertexarray.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};

struct Texture
{
	GLuint id;
	std::string type;
	aiString path;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	~Mesh();

	void draw(Shader* shader);

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	
private:
	void setupMesh();
	
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
};