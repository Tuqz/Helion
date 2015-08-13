/* 
 * File:   Image.hpp
 * Author: Ale Strooisma
 *
 * Created on August 11, 2015, 8:30 PM
 */

#ifndef IMAGE_HPP
#define	IMAGE_HPP

#include <string>
#include <memory>

class Image {
private:
	std::shared_ptr<unsigned char> data;
	int width, height, nComponents;
public:
	Image(std::string filename, int numberOfComponents = 0);
    Image(const Image& orig) = default;
    Image& operator=(const Image& orig) = default;
    Image(Image&& orig) = default;
    Image& operator=(Image&& orig) = default;
    virtual ~Image() = default;

    const unsigned char* getData() const {
        return data.get();
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

