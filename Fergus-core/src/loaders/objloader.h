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
		

		std::vector<GLfloat> vertices;
		std::vector<GLfloat> normals;
		std::vector<GLushort> indices;
		std::vector<GLfloat> texturecoords;

		for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
		{
			indices.push_back((GLushort)shapes[0].mesh.indices[i].vertex_index);
		}

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
					tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
					tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
					tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
					tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
					tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
					tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];

					vertices.push_back(vx);
					vertices.push_back(vy);
					vertices.push_back(vz);

					normals.push_back(nx);
					normals.push_back(ny);
					normals.push_back(nz);

					texturecoords.push_back(tx);
					texturecoords.push_back(ty);

					// Optional: vertex colors
					// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
					// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
					// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];


					
				}
				index_offset += fv;

				// per-face material
				shapes[s].mesh.material_ids[f];
			}
		}
		

		return RawModel(&vertices[0], vertices.size(), &normals[0], normals.size(), &indices[0], indices.size(), &texturecoords[0], texturecoords.size());
	}	

};