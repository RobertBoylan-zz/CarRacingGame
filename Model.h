#pragma once
#include <vector>
#include <GL/glew.h>
#include <C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/glm/glm/glm.hpp>
#include <C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/glm/glm/gtc/matrix_transform.hpp>
#include <C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/glm/glm/gtx/transform.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

#define TERRAIN_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Landscape.obj"
#define TREE_LEAVES_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/TreeLeaves.obj"
#define TREE_TRUNK_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/TreeTrunk.obj"
#define ROCK_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Rock.obj"
#define ROAD_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Road.obj"
#define CAR_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Car.obj"
#define CAR_PARTS_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/CarParts.obj"
#define CLOCK_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Clock.obj"
#define SKYBOX_RIGHT_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Skybox1.obj"
#define SKYBOX_LEFT_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Skybox2.obj"
#define SKYBOX_FRONT_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Skybox3.obj"
#define SKYBOX_BACK_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Skybox4.obj"
#define SKYBOX_TOP_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Skybox5.obj"
#define SKYBOX_BOTTOM_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Skybox6.obj"
#define FINISH_MESH "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Models/Finish.obj"
#define NUM_MODELS 15

using namespace std;
using glm::vec2;
using glm::vec3; 
using glm::mat4;

enum { 
	TERRAIN_MODEL, TREE_TRUNK_MODEL, TREE_LEAVES_MODEL, ROCK_MODEL, ROAD_MODEL, CAR_MODEL, CAR_PARTS_MODEL, CLOCK_MODEL, SKYBOX_RIGHT_MODEL, SKYBOX_LEFT_MODEL, 
	SKYBOX_FRONT_MODEL, SKYBOX_BACK_MODEL, SKYBOX_TOP_MODEL, SKYBOX_BOTTOM_MODEL, FINISH_MODEL
};

class Model {

public: 
	Model();

	bool LoadModel(const char* filePath, int modelID);
	void ObjectBuffer(const char* filePath, int modelID, GLuint shaderProgramID, bool textured);
	void BindTexture(GLenum textureUnit, int texNum);
	void LoadTexture(const char* fileName, int texNum);
	void DrawModel(int modelID, GLuint shaderProgramID, mat4 projection, mat4 view, vec3 camPosition, vec3 modelColour);
	void DrawTexturedModel(int modelID, GLuint shaderProgramID, int texNum, mat4 projection, mat4 view, vec3 camPosition);
	void DrawHierarchalModel(int modelID, mat4 parent, GLuint shaderProgramID, mat4 projection, mat4 view, vec3 camPosition, vec3 modelColour);
	void DrawSkybox(int modelID, GLuint shaderProgramID, int texNum, mat4 projection, mat4 view);
	void Translate1(int modelID, float x, float y, float z);
	void Translate2(int modelID, float x, float y, float z);
	void Rotate1(int modelID, float degrees, float x, float y, float z);
	void Rotate2(int modelID, float degrees, float x, float y, float z);
	void Scale1(int modelID, float scale);
	void Scale2(int modelID, float scale);
	mat4 getModelMatrix(int modelID) { return model[modelID]; }

private:
	mat4 model[NUM_MODELS];
	GLuint pointCount[NUM_MODELS], VAO[NUM_MODELS], projLocation, viewLocation, matLocation, texLocation, viewPosLocation, modelColourLocation, lightColourLocation, lightLocation;
	vector<float>points[NUM_MODELS], normals[NUM_MODELS], textures[NUM_MODELS];
	Texture texture[9];
	vec3 lightPos, lightColour;
};
