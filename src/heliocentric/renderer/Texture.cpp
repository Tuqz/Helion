/* 
 * File:   Texture.cpp
 * Author: Ale Strooisma
 * 
 * Created on August 11, 2015, 8:25 PM
 */

#include "Texture.hpp"

using namespace std;

Texture::Texture(const string& filename) : image(filename, 3) {
	initialize();
}

Texture::Texture(const Image& image) : image(image) {
	initialize();
}

void Texture::initialize() {	
	// Upload texture
	glGenTextures(1, &address);
	glBindTexture(GL_TEXTURE_2D, address);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image.getWidth(), image.getHeight(),
			0, GL_RGB, GL_UNSIGNED_BYTE, image.getData());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
}

void Texture::bindToUnit(int textureUnit) const {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, address);
}
