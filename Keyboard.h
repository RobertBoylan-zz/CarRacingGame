#pragma once
#include <GL/freeglut.h>

class Keyboard {

public:
	void KeyPressed(unsigned char key, int x, int y);
	void KeyUp(unsigned char key, int x, int y);
	void KeySpecial(int key, int x, int y);
	void KeySpecialUp(int key, int x, int y);

	enum keyStates { NOT_PUSHED, PUSHED } keyArray[1024];
	enum specialKeyStates { S_NOT_PUSHED, S_PUSHED } specialKeyArray[256];
};