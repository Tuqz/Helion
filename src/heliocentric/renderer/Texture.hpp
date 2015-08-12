/* 
 * File:   Texture.hpp
 * Author: Ale Strooisma
 *
 * Created on August 11, 2015, 8:25 PM
 */

#ifndef TEXTURE_HPP
#define	TEXTURE_HPP

#include <string>
#include "Image.hpp"
#include <GL/glew.h>

class Texture {
private:
	const Image image;
	GLuint address;
public:
	Texture(std::string filename);
	Texture(const Texture& orig) = delete;
	virtual ~Texture();
	const Image& getImage() const {
		return image;
	}
	GLuint getAddress() const {
		return address;
	}
	void bindToUnit(int unit);
};

#endif	/* TEXTURE_HPP */

