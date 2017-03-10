#pragma once
#include "Camera.h"
#include "Player.h"
#include "Scene.h"
#include "PowerUp.h"
#include "HUD.h"
#include "Keyboard.h"

#define SOUND_TRACK "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Audio/Riders_On_The_Storm.wav"

enum {
	GAME_START, GAME_RUN, GAME_OVER, GAME_WIN
};

class Game {

public:
	Game();

	void UpdateScene(); 
	void KeyPressed(unsigned char key, int x, int y);
	void KeyUp(unsigned char key, int x, int y);
	void KeySpecial(int key, int x, int y);
	void KeySpecialUp(int key, int x, int y);
	void KeyOperations();
	void SpecialKeyOperations();
	void ChangeView();
	void PlayAudio();
	void PlayerMovement();
	void CalculateStartTime();
	void CalculateGameTime();
	bool CollisionDetction(vec3 playerPosition, vec3 objectPosition);
	void ExtraTime();
	void DrawPickUps(vec3 camPosition);
	void GameStart();
	void GameOver();
	void GameWin();
	void GameDisplay();
	void GameInitialize();

private:
	GLuint shaderProgramID;
	Camera* camera;
	Player player;
	Scene scene;
	PowerUp* clock;
	HUD hud;
	Keyboard keyboard;
	mat4 view, projection;
	float moveSpeed, rotateSpeed, translation, rotation;
	int timeLeft, startTime, gameState;
	bool clockCollision1, clockCollision2, clockCollision3, clockCollision4, overHead;
	string introText, timeText, gameOverText, gameStartText, gameGoText, gameWinText;
	vec3 clockPosition[4], finishPosition, cameraPosition, cameraViewDirection;
};