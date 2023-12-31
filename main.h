#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <omp.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"

class VertexObject
{
public:
  VertexObject(const std::string& file_path)
  {
	  auto vertex = readDataFromFile(file_path);
	  glGenVertexArrays(1, &vao_);
	  glGenBuffers(1, &vbo_);
	  glBindVertexArray(vao_);
	  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	  glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);
	  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	  glEnableVertexAttribArray(0);
  }
  ~VertexObject()
  {
	  glBindBuffer(GL_ARRAY_BUFFER, 0);
	  glBindVertexArray(0);
  }
  GLuint GetVAO()
  {
    return vao_;
  }
  GLuint GetVBO()
  {
	  return vbo_;
  }
private:
	GLuint vao_;
	GLuint vbo_;
	static std::vector<GLfloat> readDataFromFile(const std::string& filename)
	{
		std::vector<GLfloat> vertexData;

		std::ifstream file(filename);
		if (!file.is_open())
		{
			std::cerr << "Failed to open file: " << filename << std::endl;
			return vertexData;
		}

		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			GLfloat x, y, z;
			if (!(iss >> x >> y >> z))
			{
				std::cerr << "Failed to parse line: " << line << std::endl;
				continue;
			}

			vertexData.push_back(x);
			vertexData.push_back(y);
			vertexData.push_back(z);
		}

		return vertexData;
	}
};



// void VAOINIT(GLuint VAO, GLuint VBO, std::vector<GLfloat> vertex)
// {
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);

// }

// std::vector<GLfloat> vertex = readDataFromFile("config/vData.txt");
// std::vector<GLfloat> cockPitvertex = readDataFromFile("config/cockPitVData.txt");
// std::vector<GLfloat> enemyvertex = readDataFromFile("onfig/enemyVData.txt");
// std::vector<GLfloat> fire1vertex = readDataFromFile("config/fire1VData.txt");
// std::vector<GLfloat> fire2vertex = readDataFromFile("config/fire2VData.txt");
// std::vector<GLfloat> missileRightRightvertex = readDataFromFile("config/missileRightRightVData.txt");
// std::vector<GLfloat> missileRightLeftvertex = readDataFromFile("config/missileRightLeftVData.txt");
// std::vector<GLfloat> missileLeftLeftvertex = readDataFromFile("config/missileLeftLeftVData.txt");
// std::vector<GLfloat> missileLeftRightvertex = readDataFromFile("missileLeftRightVData.txt");
// std::vector<GLfloat> retvertex = readDataFromFile("config/retVData.txt");
// std::vector<GLfloat> tailvertex = readDataFromFile("config/tailWingVData.txt");
// std::vector<GLfloat> wingvertex = readDataFromFile("config/wingVData.txt");
// std::vector<GLfloat> bulletvertex = readDataFromFile("config/bulletVData.txt");
// std::vector<GLfloat> thirdretvertex = readDataFromFile("config/3retVData.txt");
// std::vector<GLfloat> fieldvertex = readDataFromFile("config/fieldVData.txt");

// GLuint VAO, VBO, cockPitVAO, cockPitVBO, enemyVAO, enemyVBO, fire1VAO, fire1VBO, fire2VAO, fire2VBO, RRVAO, RRVBO, RLVAO, RLVBO, LRVAO, LRVBO, LLVAO, LLVBO, retVAO, retVBO, wingVAO, wingVBO, tailVAO, tailVBO, bulletVAO, bulletVBO, thirdretVAO, thirdretVBO, fieldVAO, fieldVBO;

// VAOINIT(VAO, VBO, vertex);
// VAOINIT(cockPitVAO, cockPitVBO, cockPitvertex);
// VAOINIT(enemyVAO, enemyVBO, enemyvertex);
// VAOINIT(fire1VAO, fire1VBO, fire1vertex);
// VAOINIT(fire2VAO, fire2VBO, fire2vertex);
// VAOINIT(RRVAO, RRVBO, missileRightRightvertex);
// VAOINIT(RLVAO, RLVBO, missileRightLeftvertex);
// VAOINIT(LRVAO, LRVBO, missileLeftRightvertex);
// VAOINIT(LLVAO, LLVBO, missileLeftLeftvertex);
// VAOINIT(retVAO, retVBO, retvertex);
// VAOINIT(thirdretVAO, thirdretVBO, thirdretvertex);
// VAOINIT(tailVAO, tailVBO, tailvertex);
// VAOINIT(wingVAO, wingVBO, wingvertex);
// VAOINIT(bulletVAO, bulletVBO, bulletvertex);
// VAOINIT(fieldVAO, fieldVBO, fieldvertex);
