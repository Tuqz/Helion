/* 
 * File:   Image.hpp
 * Author: Ale Strooisma
 *
 * Created on August 11, 2015, 8:30 PM
 */

#ifndef IMAGE_HPP
#define	IMAGE_HPP

#include <string>

class Image {
private:
	unsigned char *data;
	int width, height, nComponents;
public:
	Image(std::string filename, int numberOfComponents = 0);
	Image(const Image& orig) = delete;
	virtual ~Image();
	unsigned char* getData() const {
		return data;
	}
	int getHeight() const {
		return height;
	}
	int getNumberOfComponents() const {
		return nComponents;
	}
	int getWidth() const {
		return width;
	}
};

#endif	/* IMAGE_HPP */

