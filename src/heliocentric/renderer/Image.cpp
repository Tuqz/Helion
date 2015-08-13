/* 
 * File:   Image.cpp
 * Author: Ale Strooisma
 * 
 * Created on August 11, 2015, 8:30 PM
 */

#include "Image.hpp"
#include "../exceptions.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

using namespace std;

Image::Image(string filename, int numberOfComponents) 
: data(stbi_load(filename.c_str(), &width, &height, &nComponents, numberOfComponents), stbi_image_free) {
	if (getData() == nullptr) {
		throw IOException("Unable to read \"" + filename + "\": " + stbi_failure_reason());
	}
}

