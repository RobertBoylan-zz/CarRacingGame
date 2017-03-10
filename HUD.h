#pragma once
#include <GL/freeglut.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

class HUD {

public:
	
	HUD();

	void Text(const char* text, int length, int x, int y);
};
