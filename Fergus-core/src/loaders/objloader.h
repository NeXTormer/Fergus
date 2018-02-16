#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <array>

#include "../fergus.h"
#include "../utils/fileutils.h"
#include "../utils/timer.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

//using https://github.com/syoyo/tinyobjloader

class OBJLoader
{
public:
	static RawModel TestLoadObj(const char* filename, const char* basepath = NULL,
		bool triangulate = false) {
		std::cout << "Loading " << filename << std::endl;

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		Timer t;
		t.reset();
		std::string err;
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, triangulate);
		std::cout << "Parsing Time: " << t.elapsed() << std::endl;

		if (!err.empty()) {
			std::cerr << err << std::endl;
		}

		if (!ret) {
			printf("Failed to load/parse .obj.\n");
		}

		std::vector<GLushort> indices_t;

		for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
		{
			indices_t.push_back((GLushort)shapes[0].mesh.indices[i].vertex_index);
		}

		return RawModel(&attrib.vertices[0], attrib.vertices.size(), &indices_t[0], indices_t.size(), &attrib.texcoords[0], attrib.texcoords.size());
	}	
};