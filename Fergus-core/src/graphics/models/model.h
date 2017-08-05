#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "mesh.h"
#include "../shader.h"
#include "../../utils/stb_image.h"

class Model
{
public:
	Model(std::string path) { loadModel(path); }

	void draw(Shader* shader);

private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;
	
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	GLuint loadTextureFromFile(const char* path, const std::string& dir);



};