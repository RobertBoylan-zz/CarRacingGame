#pragma once
#include "Model.h"
#include "Player.h"

class PowerUp {
public:
	PowerUp(vec3 Position);
	void Load();
	void Draw(mat4 projection, mat4 view, vec3 Position, float translation, float rotation, vec3 camPosition);
	void Transformation(float translation, float rotation);

private:
	const char* fileName;
	vec3 position, playerPosition;
	Model clock;
	Shader* shader;
	Player player;
	GLuint clockShaderProgramID;
};