#include "Game.h"

Game::Game() :
	finishPosition(5.265f, 0.0f, -4.0f),
	cameraViewDirection(0.0f, -25.0f, 3.0f)
{
	moveSpeed = 0.0f;
	rotateSpeed = 0.0f;
	translation = 0.0f;
	rotation = 0.0f;
	gameState = GAME_START;
	camera = NULL;
	clock = NULL;
	introText = "Race Car Game";
	gameGoText = "GO";
	gameOverText = "GAME OVER";
	gameWinText = "YOU WON!";
	overHead = false;
	clockCollision1 = false;
	clockCollision2 = false;
	clockCollision3 = false;
	clockCollision4 = false;
	clockPosition[0] = vec3(-2.0f, 0.07f, 6.3f);
	clockPosition[1] = vec3(-1.56f, 0.07f, -0.3f);
	clockPosition[2] = vec3(-1.56f, 0.07f, -5.6f);
	clockPosition[3] = vec3(4.7f, 0.07f, -5.6f);
	cameraPosition.x = player.getStartPosition().x;
	cameraPosition.y = player.getStartPosition().y + 25.1f;
	cameraPosition.z = player.getStartPosition().z - 0.25f;
	camera = new Camera(cameraPosition, cameraViewDirection);
}

void Game::UpdateScene() {

	static DWORD  lastTime = 0;
	DWORD  currentTime = timeGetTime();
	float  delta = (currentTime - lastTime) * 0.001f;
	if (delta > 0.03f) {
		delta = 0.03f;
	}
	lastTime = currentTime;

	translation += 0.005f;
	rotation += 0.0015f;

	glutPostRedisplay();
}

void Game::KeyPressed(unsigned char key, int x, int y) {

	keyboard.KeyPressed(key, x, y);
}

void Game::KeyUp(unsigned char key, int x, int y) {

	keyboard.KeyUp(key, x, y);
}
void Game::KeySpecial(int key, int x, int y) {

	keyboard.KeySpecial(key, x, y);
}
void Game::KeySpecialUp(int key, int x, int y) {

	keyboard.KeySpecialUp(key, x, y);
}

void Game::KeyOperations() {

	if (keyboard.keyArray['d']) {
		
		if (!overHead) {
			
			camera->RotateRight(player.getRotateSpeed());
		}
		player.RotateCarRight();
	}
	if (keyboard.keyArray['a']) {
		
		if (!overHead) {
			
			camera->RotateLeft(player.getRotateSpeed());
		}
		player.RotateCarLeft();
	}
	if (keyboard.keyArray['w']) {
		
		if (!overHead) {
			
			camera->MoveForward(player.getMoveSpeed() / 200.0f);
		}
		player.Forward();
	}
	if (keyboard.keyArray['s']) {
		
		if (!overHead) {
			
			camera->MoveBackward(player.getMoveSpeed() / 200.0f);
		}
		player.Reverse();
	}
	if (keyboard.keyArray[' ']) {
		player.Brake();
	}
}

void Game::SpecialKeyOperations() {

	if (keyboard.specialKeyArray[GLUT_KEY_RIGHT]) {
		camera->RotateRight(player.getRotateSpeed());
	}
	if (keyboard.specialKeyArray[GLUT_KEY_LEFT]) {
		camera->RotateLeft(player.getRotateSpeed());
	}
	if (keyboard.specialKeyArray[GLUT_KEY_UP]) {
		
		camera->MoveForward(0.1f);
	}
	if (keyboard.specialKeyArray[GLUT_KEY_DOWN]) {
		
		overHead = !overHead;
	}
}

void Game::ChangeView() {

	if (overHead) {

		if (camera->getPosition().x < 0.0f) {
			
			camera->StrafeLeft(0.01f);
		}
		if (camera->getPosition().x > 0.0f) {
			
			camera->StrafeRight(0.01f);
		}
		if (camera->getPosition().z > 0.0f) {
			
			camera->MoveForward(0.01f);
		}
		if (camera->getPosition().z < 0.0f) {
			
			camera->MoveBackward(0.01f);
		}
		if (camera->getPosition().y < 14.0f) {

			camera->MoveUp(0.01f);
		}
		if (camera->getViewDirection().x > 0.0f) {
			
			camera->RotateLeft(0.003f);
		}
		if (camera->getViewDirection().x < 0.0f) {
			
			camera->RotateRight(0.003f);
		}
		if (camera->getViewDirection().y > -25.0f) {
			
			camera->RotateDown(0.003f);
		}
	}
}

void Game::PlayAudio() {

	PlaySound(TEXT(SOUND_TRACK), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}

void Game::PlayerMovement() {

	player.Decelerate();
	player.Move();
	player.RotationSpeed();

	if (!player.getAccelerationState() && !overHead) {

		camera->MoveForward(player.getMoveSpeed() / 40.0f);
	}
	if (player.getAccelerationState() && !overHead) {

		camera->MoveBackward(player.getMoveSpeed() / 40.0f);
	}
}

void Game::CalculateStartTime() {

	int elapsedTime = (int)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	startTime = 14 - elapsedTime;
}

void Game::CalculateGameTime() {

	int elapsedTime = (int)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	timeLeft = 56 - elapsedTime;
}

bool Game::CollisionDetction(vec3 playerPosition, vec3 objectPosition) {

	float distance = sqrt(pow((playerPosition.x - objectPosition.x), 2) + pow((playerPosition.z - objectPosition.z), 2));

	if (distance <= 0.34f) {

		return true;
	}

	return false;
}

void Game::ExtraTime() {

	if (CollisionDetction(clockPosition[0], cameraPosition)) {

		clockCollision1 = true;
	}

	if (CollisionDetction(clockPosition[1], cameraPosition)) {

		clockCollision2 = true;
	}

	if (CollisionDetction(clockPosition[2], cameraPosition)) {

		clockCollision3 = true;
	}

	if (CollisionDetction(clockPosition[3], cameraPosition)) {

		clockCollision4 = true;
	}
}

void Game::DrawPickUps(vec3 camPosition) {

	if (!clockCollision1) {

		clock->Draw(projection, view, clockPosition[0], translation, rotation, camPosition);
	}

	if (clockCollision1) {
		
		timeLeft += 10;
	}

	if (!clockCollision2) {

		clock->Draw(projection, view, clockPosition[1], translation, rotation, camPosition);
	}

	if (clockCollision2) {
		
		timeLeft += 10;
	}

	if (!clockCollision3) {

		clock->Draw(projection, view, clockPosition[2], translation, rotation, camPosition);
	}

	if (clockCollision3) {
		
		timeLeft += 10;
	}

	if (!clockCollision4) {

		clock->Draw(projection, view, clockPosition[3], translation, rotation, camPosition);
	}

	if (clockCollision4) {
		
		timeLeft += 10;
	}
}

void Game::GameStart() {

	if (startTime <= -2) {

		gameState = GAME_RUN;
	}
}

void Game::GameOver() {

	if (timeLeft <= 0) {

		gameState = GAME_OVER;
	}
}

void Game::GameWin() {

	if (CollisionDetction(finishPosition, cameraPosition)) {

		gameState = GAME_WIN;
	}
}


void Game::GameDisplay() {

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.6f, 0.6f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cameraPosition = camera->getPosition();
	view = camera->getWorldToViewMatrix();
	projection = glm::perspective(45.0f, ((float)WINDOW_WIDTH) / ((float)WINDOW_WIDTH), 0.1f, 600.0f);

	scene.Draw(projection, view, cameraPosition);
	DrawPickUps(cameraPosition);
	player.Draw(projection, view, cameraPosition);

	if (gameState == GAME_START) {

		if (camera->getPosition().y > player.getStartPosition().y + 0.1f) {

			camera->MoveDown(0.01f);
			hud.Text(introText.data(), introText.size(), WINDOW_WIDTH / 2 - 30, WINDOW_HEIGHT / 2 - 5);
		}
		
		if ((camera->getViewDirection().y < -1.0f) && (camera->getPosition().y <= player.getStartPosition().y + 0.1f)) {
			
			camera->RotateUp(0.003f);
		}
		CalculateStartTime();
		GameStart();
		gameStartText = to_string(startTime);

		if (startTime > 0 && startTime <= 3) {
			
			hud.Text(gameStartText.data(), gameStartText.size(), WINDOW_WIDTH / 2 - 30, WINDOW_HEIGHT - 20);
		}
		if (startTime <= 0) {
			
			hud.Text(gameGoText.data(), gameGoText.size(), WINDOW_WIDTH / 2 - 30, WINDOW_HEIGHT - 20);
		}
	}

	else if (gameState == GAME_RUN) {

		KeyOperations();
		SpecialKeyOperations();
		ChangeView();
		PlayerMovement();
		CalculateGameTime();
		ExtraTime();
		DrawPickUps(cameraPosition);
		player.Draw(projection, view, cameraPosition);
		GameOver();
		GameWin();
		timeText = to_string(timeLeft);
		hud.Text(timeText.data(), timeText.size(), WINDOW_WIDTH / 2 - 30, WINDOW_HEIGHT - 20);
	}

	else if (gameState == GAME_OVER) {

		camera->RotateDown(0.003f);
		camera->MoveUp(0.01f);
		PlayerMovement();
		hud.Text(gameOverText.data(), gameOverText.size(), WINDOW_WIDTH / 2 - 30, WINDOW_HEIGHT / 2 - 5);
	}

	else if (gameState == GAME_WIN) {

		PlayerMovement();
		hud.Text(gameWinText.data(), gameWinText.size(), WINDOW_WIDTH / 2 - 30, WINDOW_HEIGHT / 2 - 5);
	}

	glutSwapBuffers();
}

void Game::GameInitialize() {

	player.Load();

	for (int i = 0; i < 4; i++) {
		
		clock = new PowerUp(clockPosition[i]);
		clock->Load();
	}
	
	scene.Load();
}