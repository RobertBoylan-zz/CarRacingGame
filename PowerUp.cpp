#include "PowerUp.h"

PowerUp::PowerUp(vec3 Position) {

	shader = NULL;
	position = Position;
}

void PowerUp::Load() {

	shader = new Shader(LIGHT_VERTEX_SHADER, LIGHT_FRAGMENT_SHADER);
	clockShaderProgramID = shader->CompileShaders();

	clock.ObjectBuffer(CLOCK_MESH, CLOCK_MODEL, clockShaderProgramID, false);
}

void PowerUp::Draw(mat4 projection, mat4 view, vec3 Position, float translation, float rotation, vec3 camPosition) {

	position = Position;

	clock.Translate2(TERRAIN_MODEL, position.x, position.y, position.z);
	clock.Translate2(CLOCK_MODEL, position.x, position.y, position.z);
	Transformation(translation, rotation);

	clock.DrawModel(CLOCK_MODEL, clockShaderProgramID, projection, view, camPosition, vec3(1.0f, 1.0f, 0.1f));
}

void PowerUp::Transformation(float translation, float rotation) {

	clock.Rotate1(CLOCK_MODEL, rotation, 0.0f, 1.0f, 0.0f);
	clock.Translate1(CLOCK_MODEL, 0.0f, sin(translation)/20, 0.0f);
}