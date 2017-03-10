#include <C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/glm/glm/gtx/transform.hpp>
#include "Camera.h"

const float Camera::moveSpeed = 0.01f;
const float Camera::rotateSpeed = 0.003f;

using glm::vec2;
using glm::vec3;
using glm::mat4;

Camera::Camera(vec3 Position, vec3 ViewDirection) :
	viewDirection(0.0f, -25.0f, 3.0f),
	UP(0.0f, 1.0f, 0.0f)
{
	yaw = PI / 2;
	pitch = 0.0f;
	position = Position;
	viewDirection = ViewDirection;
}

mat4 Camera::getWorldToViewMatrix() const {

	return glm::lookAt(position, position + viewDirection, UP);
}

void Camera::Refresh() {
	viewDirection.x = cos(yaw) * cos(pitch);
	viewDirection.y = sin(pitch);
	viewDirection.z = sin(yaw) * cos(pitch);
}

void Camera::RotateYaw(float angle) {
	yaw += angle;

	Refresh();
}

void Camera::RotatePitch(float angle)
{
	const float limit = 89.0 * PI / 180.0;

	pitch += angle;

	if (pitch < -limit)
		pitch = -limit;

	if (pitch > limit)
		pitch = limit;

	Refresh();
}

void Camera::MoveForward(float moveSpeed)
{
	position.x += viewDirection.x * moveSpeed;
	position.z += viewDirection.z * moveSpeed;
}

void Camera::MoveBackward(float moveSpeed)
{
	position.x += viewDirection.x * -moveSpeed;
	position.z += viewDirection.z * -moveSpeed;
}

void Camera::StrafeLeft(float moveSpeed)
{
	strafeDirection = cross(viewDirection, UP);
	position += strafeDirection * -moveSpeed;
}

void Camera::StrafeRight(float moveSpeed)
{
	strafeDirection = cross(viewDirection, UP);
	position += strafeDirection * moveSpeed;
}

void Camera::MoveUp(float moveSpeed)
{
	position += UP * moveSpeed;
}

void Camera::MoveDown(float moveSpeed)
{
	position -= UP * moveSpeed;
}

void Camera::RotateUp(float rotateSpeed)
{
	RotatePitch(rotateSpeed);
}

void Camera::RotateDown(float rotateSpeed)
{
	RotatePitch(-rotateSpeed);
}

void Camera::RotateLeft(float rotateSpeed)
{
	RotateYaw(-rotateSpeed);
}

void Camera::RotateRight(float rotateSpeed)
{
	RotateYaw(rotateSpeed);
}