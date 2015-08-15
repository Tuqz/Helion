/* 
 * File:   Texture.hpp
 * Author: Ale Strooisma
 *
 * Created on August 11, 2015, 8:25 PM
 */

#ifndef TEXTURE_HPP
#define	TEXTURE_HPP

#include <string>
#include <GL/glew.h>
#include "Image.hpp"

class Texture {
private:
	const Image image;
	GLuint address;
public:
	Texture(const std::string& filename);
	Texture(const Image& image);
	Texture(const Texture& orig) = delete;
	virtual ~Texture();
	const Image& getImage() const {
		return image;
	}
	GLuint getAddress() const {
		return address;
	}
	void bindToUnit(int unit) const;
private:
	void initialize();
};

#endif	/* TEXTURE_HPP */

