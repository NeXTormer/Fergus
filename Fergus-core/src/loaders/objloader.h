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

typedef std::array<GLfloat, 3> loader_vec3f;
typedef std::array<float, 2> loader_vec2f;

///Credit to https://github.com/Hopson97/ThinMatrix-OpenGL-Engine/blob/c7bd1f2bf5dc1a32f0b1b49173b28f6a3aeb7755/Source/Render_Engine/OBJLoader.cpp
class OBJLoader
{
public:
	static void split(const std::string &s, char delim, std::vector<std::string>& elems)
	{
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}

	std::vector<std::string> split(const std::string& s, char delim)
	{
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}

	static void processVertex(const  std::vector<std::string>&   vertexData,
		const  std::vector<glm::vec3> &      normals,
		const  std::vector<glm::vec2> &      textures,
		std::vector<GLuint>  &      indices,
		std::vector<GLfloat> &      textureArray,
		std::vector<GLfloat> &      normalArray)
	{
		std::cout << vertexData.at(0) << std::endl;
		GLuint currentVertexPointer = std::stoi(vertexData.at(0)) - 1;
		indices.push_back(currentVertexPointer);

		glm::vec2 currentTexture = textures.at(std::stoi(vertexData.at(1)) - 1);
		textureArray[currentVertexPointer * 2] = currentTexture.x;
		textureArray[currentVertexPointer * 2 + 1] = 1 - currentTexture.y;

		glm::vec3 currentNorm = normals.at(std::stoi(vertexData.at(2)) - 1);
		normalArray[currentVertexPointer * 3] = currentNorm.x;
		normalArray[currentVertexPointer * 3 + 1] = currentNorm.y;
		normalArray[currentVertexPointer * 3 + 2] = currentNorm.z;
	}
	
	//The code below this comment was not written by me, so all credit goes to github use Ruixel
	template<typename T>
	static void insertIntoFloatVector(std::vector<T>* vec, std::istringstream* ss,
		size_t arraySize)
	{
		std::array<std::string, 3> x;
		ss->seekg(2);

		if (arraySize == 2)
			*ss >> x[0] >> x[1];
		else
			*ss >> x[0] >> x[1] >> x[2];

		T tArray;
		for (size_t i = 0; i<arraySize; i++)
			tArray[i] = stof(x[i]);
		vec->push_back(tArray);

	}

	static void insertIntoStringVector(std::vector<std::string>* vec, std::istringstream* ss)
	{
		std::array<std::string, 3> x;
		ss->seekg(2);

		*ss >> x[0] >> x[1] >> x[2];

		for (int i = 0; i<3; i++)
			vec->push_back(x[i]);
	}

	static RawModel loadModel(const std::string& fileName)
	{
		// OBJ File Vectors
		std::vector<loader_vec3f> vertices, normals;
		std::vector<loader_vec2f> textureCoordinates;
		std::vector<std::string> faces;

		// VBO Arrays
		std::vector<GLfloat> a_vertices, a_texCoords, a_normals;
		std::vector<GLushort>  a_indices;

		// File Buffer Objects
		std::ifstream file;
		std::stringstream obj;
		file.exceptions(std::ifstream::badbit);

		// Attempt to read file, if error occurs it returns a nullptr
		try {
			file.open(fileName);
			obj << file.rdbuf();
			file.close();

		}
		catch (std::ios_base::failure e) {
			std::cout << "Error loading " << fileName << std::endl;
			//return nullptr;
		}

		// Read the buffer and place into separate vectors to process later
		std::string line;
		while (std::getline(obj, line))
		{
			std::istringstream ss(line);

			if (ss.peek() == 'v')
			{
				ss.seekg(1);

				// Vertex
				if (ss.peek() == ' ')
					insertIntoFloatVector(&vertices, &ss, 3);
				else if (ss.peek() == 't')
					insertIntoFloatVector(&textureCoordinates, &ss, 2);
				else if (ss.peek() == 'n')
					insertIntoFloatVector(&normals, &ss, 3);
			}

			if (ss.peek() == 'f')
				insertIntoStringVector(&faces, &ss);
		}

		// From vector<array>s into single <arrays>
		std::array<std::string, 3> a;
		GLfloat glf[3];
		int pointAt, indexCount = 0;
		std::string str;
		for (auto& i : faces)
		{
			std::istringstream ss(i);

			pointAt = 0;
			while (getline(ss, str, '/')) {
				glf[pointAt] = stoi(str);
				pointAt++;
			}

			//cout << vertices.at(glf[pointAt]-1).at(0) << endl;
			//cout << textureCoordinates.at(glf[1]-1).at(v) << endl;

			// VBO
			for (int v = 0; v < 3; v++)
				a_vertices.push_back(vertices.at(glf[0] - 1).at(v));

			for (int v = 0; v < 2; v++)
			{
				a_texCoords.push_back(textureCoordinates.at(glf[1] - 1).at(v));
			}

			for (int v = 0; v < 3; v++) {
				a_normals.push_back(normals.at(glf[2] - 1).at(v));
			}

			for (int v = 0; v < 3; v++) {
				a_indices.push_back(indexCount);
				indexCount++;
			}

		}

		return RawModel(&a_vertices[0], a_vertices.size(), &a_indices[0], a_vertices.size(), &a_texCoords[0], a_vertices.size());
	}


};