#pragma once
#include "Model.h"

class Player
{
public:
	Player();

	void Load();
	void Draw(mat4 projection, mat4 view, vec3 camPosition);
	void Accelerate(bool reverse);
	void Decelerate();
	void Refresh();
	void Forward();
	void Reverse();
	void Move();
	void RotateCarLeft();
	void RotateCarRight();
	void RotationSpeed();
	void Brake();
	void Cornering();
	vec3 getStartPosition() { return startPosition; }
	vec3 getPosition() { return carPosition; }
	vec3 getViewDirection() { return carDirection; }
	float getMoveSpeed() { return moveSpeed; }
	float getRotateSpeed() { return rotateSpeed; }
	float getDistanceX() { return distanceX; }
	float getDistanceZ() { return distanceZ; }
	bool getAccelerationState() { return reverse; }

private:
	vec3 startPosition, carPosition, carDirection;
	float moveSpeed, yaw, rotateSpeed, distanceX, distanceZ;
	static const float acceleration, deceleration, maxSpeedF, maxSpeedR, maxRotationSpeed, brakePower;
	bool reverse;
	Model car, carParts, cameraOrigin;
	GLuint carShaderProgramID, carPartsShaderProgramID;
	Shader* carShader; 
	Shader* carPartsShader;
};
