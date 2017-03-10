#include "Game.h"

#pragma region DEFINITIONS

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define NUM_EXTRA_TIME 4

#pragma endregion DEFINITION

Game* game;

void Display() {

	game->GameDisplay();
}

void Update() {

	game->UpdateScene();
}

void KeyPressed(unsigned char key, int x, int y) {

	game->KeyPressed(key, x, y);
}

void KeyUp(unsigned char key, int x, int y) {

	game->KeyUp(key, x, y);
}
void KeySpecial(int key, int x, int y) {

	game->KeySpecial(key, x, y);
}
void KeySpecialUp(int key, int x, int y) {

	game->KeySpecialUp(key, x, y);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
	glutCreateWindow("Rob's Fantastic Game");

	game = new Game();

	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(KeySpecial);
	glutSpecialUpFunc(KeySpecialUp);
	glutDisplayFunc(Display);
	glutIdleFunc(Update);

	GLenum res = glewInit();

	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	game->GameInitialize();
	game->PlayAudio();

	glutMainLoop();
	return 0;
}