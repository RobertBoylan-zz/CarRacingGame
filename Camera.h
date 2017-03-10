#pragma once
#include <C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/glm/glm/glm.hpp>

#define PI 3.14159265358979323846f

using glm::vec2;
using glm::vec3;
using glm::mat4;

class Camera
{

public:
	Camera(vec3 Position, vec3 ViewDirection);

	mat4 getWorldToViewMatrix() const;
	vec3 getPosition() const { return position; }
	vec3 getViewDirection() const { return viewDirection; }
	vec3 getUP() const { return UP; }
	void Refresh();
	void RotateYaw(float angle);
	void RotatePitch(float angle);
	void MoveForward(float moveSpeed);
	void MoveBackward(float moveSpeed);
	void StrafeLeft(float moveSpeed);
	void StrafeRight(float moveSpeed);
	void MoveUp(float moveSpeed);
	void MoveDown(float moveSpeed);
	void RotateUp(float rotateSpeed);
	void RotateDown(float rotateSpeed);
	void RotateLeft(float rotateSpeed);
	void RotateRight(float rotateSpeed);

private:
	vec3 position, viewDirection, UP, strafeDirection;
	static const float moveSpeed, rotateSpeed;
	float yaw, pitch, distance;
};