#include "Texture.h"

Texture::Texture() {}

bool Texture::Load(const char* fileName, int texNum) {

	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGB);

	glGenTextures(1, &textureID[texNum]);
	glBindTexture(GL_TEXTURE_2D, textureID[texNum]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void Texture::Bind(GLenum TextureUnit, int texNum) {
	
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID[texNum]);
}