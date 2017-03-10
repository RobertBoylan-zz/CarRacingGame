#include "Keyboard.h"

void Keyboard::KeyPressed(unsigned char key, int x, int y) {

	if (key == 'd') {
		keyArray[int('d')] = PUSHED;
	}
	if (key == 'w') {
		keyArray[int('w')] = PUSHED;
	}
	if (key == 'a') {
		keyArray[int('a')] = PUSHED;
	}
	if (key == 's') {
		keyArray[int('s')] = PUSHED;
	}
	if (key == ' ') {
		keyArray[int(' ')] = PUSHED;
	}
	glutPostRedisplay();
}

void Keyboard::KeyUp(unsigned char key, int x, int y) {

	if (key == 'd') {
		keyArray[int('d')] = NOT_PUSHED;
	}
	if (key == 'w') {
		keyArray[int('w')] = NOT_PUSHED;
	}
	if (key == 'a') {
		keyArray[int('a')] = NOT_PUSHED;
	}
	if (key == 's') {
		keyArray[int('s')] = NOT_PUSHED;
	}
	if (key == ' ') {
		keyArray[int(' ')] = NOT_PUSHED;
	}
	glutPostRedisplay();
}

void Keyboard::KeySpecial(int key, int x, int y) {

	if (key == GLUT_KEY_RIGHT) {
		specialKeyArray[int(GLUT_KEY_RIGHT)] = S_PUSHED;
	}
	if (key == GLUT_KEY_LEFT) {
		specialKeyArray[int(GLUT_KEY_LEFT)] = S_PUSHED;
	}
	if (key == GLUT_KEY_UP) {
		specialKeyArray[int(GLUT_KEY_UP)] = S_PUSHED;
	}
	if (key == GLUT_KEY_DOWN) {
		specialKeyArray[int(GLUT_KEY_DOWN)] = S_PUSHED;
	}
	glutPostRedisplay();
}

void Keyboard::KeySpecialUp(int key, int x, int y) {

	if (key == GLUT_KEY_RIGHT) {
		specialKeyArray[int(GLUT_KEY_RIGHT)] = S_NOT_PUSHED;
	}
	if (key == GLUT_KEY_LEFT) {
		specialKeyArray[int(GLUT_KEY_LEFT)] = S_NOT_PUSHED;
	}
	if (key == GLUT_KEY_UP) {
		specialKeyArray[int(GLUT_KEY_UP)] = S_NOT_PUSHED;
	}
	if (key == GLUT_KEY_DOWN) {
		specialKeyArray[int(GLUT_KEY_DOWN)] = S_NOT_PUSHED;
	}
	glutPostRedisplay();
}