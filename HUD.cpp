#include "HUD.h"

HUD::HUD() {}

void HUD::Text(const char* text, int length, int x, int y) {

	glMatrixMode(GL_PROJECTION);
	double matrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);

	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}