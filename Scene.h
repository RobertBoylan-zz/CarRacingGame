#pragma once
#include "Shader.h"
#include "Model.h"

class Scene {

public:
	Scene();

	void Load();
	void Draw(mat4 projection, mat4 view, vec3 camPosition);

private:
	Model terrain, road, treeTrunk, treeLeaves, rock, mountain, finish, skyboxFront, skyboxBack, skyboxLeft, skyboxRight, skyboxTop, skyboxBottom;
	Shader* texturedModelShader; 
	Shader* skyboxShader;
	GLuint texturedModelShaderProgramID, skyboxShaderProgramID, lightShaderProgramID, skyboxTexture;
};