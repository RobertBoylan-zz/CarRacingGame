#include "Player.h"

const float Player::acceleration = 0.000012f;
const float Player::deceleration = 0.000003f;
const float Player::maxSpeedF = 0.08f;
const float Player::maxSpeedR = 0.055f;
const float Player::maxRotationSpeed = 0.005f;
const float Player::brakePower = 0.0001f;

Player::Player() :
	startPosition(5.28f, -0.02f, -2.5f),
	carDirection(0.0f, 0.0f, 1.0f)
{
	carShader = NULL;
	carPartsShader = NULL;
	reverse = false;
	yaw = 0;
	moveSpeed = 0.0f;
	rotateSpeed = 0.0f;
	carPosition = startPosition;
	car.Translate2(CAR_MODEL, carPosition.x, carPosition.y, carPosition.z);
	carParts.Translate2(CAR_PARTS_MODEL, carPosition.x, carPosition.y, carPosition.z);
	car.Scale1(CAR_MODEL, 0.03f);
	carParts.Scale1(CAR_PARTS_MODEL, 0.03f);
}

void Player::Load() {

	carShader = new Shader(LIGHT_VERTEX_SHADER, LIGHT_FRAGMENT_SHADER);
	carShaderProgramID = carShader->CompileShaders();

	carPartsShader = new Shader(LIGHT_VERTEX_SHADER, LIGHT_FRAGMENT_SHADER);
	carPartsShaderProgramID = carPartsShader->CompileShaders();

	car.ObjectBuffer(CAR_MESH, CAR_MODEL, carShaderProgramID, false);
	carParts.ObjectBuffer(CAR_PARTS_MESH, CAR_PARTS_MODEL, carPartsShaderProgramID, false);
}

void Player::Draw(mat4 projection, mat4 view, vec3 camPosition) {

	car.DrawModel(CAR_MODEL, carShaderProgramID, projection, view, camPosition, vec3(0.8f, 0.0f, 0.0f));
	carParts.DrawModel(CAR_PARTS_MODEL, carPartsShaderProgramID, projection, view, camPosition, vec3(0.0f, 0.0f, 0.0f));
}

void Player::Accelerate(bool reverse) {

	if (reverse == false) {
		if (moveSpeed <= maxSpeedF) {
			moveSpeed += acceleration;
		}
	}
	else {
		if (moveSpeed <= maxSpeedR) {
			moveSpeed += acceleration;
		}
	}
}

void Player::Decelerate() {
	
	if (moveSpeed > 0) {
		moveSpeed -= deceleration;
	}

	if (rotateSpeed > 0) {
		rotateSpeed -= (deceleration - 0.000003f);
	}
}

void Player::Forward() {

	reverse = false;
	Accelerate(reverse);

	carPosition.z = startPosition.z + moveSpeed;

	distanceZ = carPosition.z - startPosition.z;
}

void Player::Reverse(){

	reverse = true;
	Accelerate(reverse);

	distanceZ = carPosition.z - startPosition.z;

	carPosition.z = startPosition.z - moveSpeed;
}

void Player::Move() {

	if (moveSpeed > 0) {
	
		car.Translate1(CAR_MODEL, distanceX, 0.0f, distanceZ);
		carParts.Translate1(CAR_PARTS_MODEL, distanceX, 0.0f, distanceZ);
	}
}

void Player::RotateCarLeft() {

	if (!reverse) {
		car.Rotate1(CAR_MODEL, rotateSpeed, 0.0f, 1.0f, 0.0f);
		carParts.Rotate1(CAR_PARTS_MODEL, rotateSpeed, 0.0f, 1.0f, 0.0f);
		Cornering();
	}

	else {

		car.Rotate1(CAR_MODEL, -rotateSpeed, 0.0f, 1.0f, 0.0f);
		carParts.Rotate1(CAR_PARTS_MODEL, -rotateSpeed, 0.0f, 1.0f, 0.0f);
		Cornering();
	}
}

void Player::RotateCarRight() {

	if (!reverse) {
		car.Rotate1(CAR_MODEL, -rotateSpeed, 0.0f, 1.0f, 0.0f);
		carParts.Rotate1(CAR_PARTS_MODEL, -rotateSpeed, 0.0f, 1.0f, 0.0f);
		Cornering();
	}

	else {

		car.Rotate1(CAR_MODEL, rotateSpeed, 0.0f, 1.0f, 0.0f);
		carParts.Rotate1(CAR_PARTS_MODEL, rotateSpeed, 0.0f, 1.0f, 0.0f);
		Cornering();
	}
}

void Player::RotationSpeed() {

	if ((moveSpeed > 0) && (moveSpeed < (maxSpeedF / 4)) && rotateSpeed <= maxRotationSpeed) {

		rotateSpeed += (acceleration - 0.000008f);
	}
	if ((moveSpeed >= (maxSpeedF / 4)) && (moveSpeed < (3 * maxSpeedF / 4)) && rotateSpeed <= maxRotationSpeed) {

		rotateSpeed += (acceleration - 0.000009f);
	}
	if ((moveSpeed >= (3 * maxSpeedF / 4)) && (moveSpeed < maxSpeedF) && rotateSpeed <= maxRotationSpeed) {

		rotateSpeed += (acceleration - 0.0000099f);
	}
}

void Player::Brake() {

	if (moveSpeed > 0) {
		moveSpeed -= brakePower;
	}
	if (rotateSpeed > 0) {
		rotateSpeed -= (brakePower - 0.000088f);
	}
}

void Player::Cornering() {

	if (moveSpeed >= (maxSpeedF - 0.008)) {

		moveSpeed -= (deceleration - 0.00002);
	}
}