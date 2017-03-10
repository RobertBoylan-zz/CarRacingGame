#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>

#define TERRAIN_TEXTURE "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Images/grass.jpg"
#define LEAF_TEXTURE "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Images/tree.jpg"
#define BARK_TEXTURE "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Images/bark.jpg"
#define ROCK_TEXTURE "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Images/rock.jpg"
#define ROAD_TEXTURE "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Images/road.jpg"
#define SKYBOX_TEXTURE "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Images/sky.jpg"
#define FINISH_TEXTURE "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Images/finish.jpg"

#define NUM_TEXTURES 7

using namespace std;

enum {
	TERRAIN_TEXT, ROAD_TEXT, BARK_TEXT, LEAF_TEXT, ROCK_TEXT, SKYBOX_TEXT, FINISH_TEXT
};

class Texture
{
public:
	Texture();

	bool Load(const char* fileName, int texNum);
	void Bind(GLenum TextureUnit, int texnum);

private:
	int width, height;
	GLuint textureID[9];
	const char* fileName;
};
