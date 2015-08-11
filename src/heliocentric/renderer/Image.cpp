/* 
 * File:   Image.cpp
 * Author: Ale Strooisma
 * 
 * Created on August 11, 2015, 8:30 PM
 */

#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

using namespace std;

Image::Image(string filename, int numberOfComponents) {
    data = stbi_load(filename.c_str(), &width, &height, &nComponents, numberOfComponents);
}

Image::~Image() {
	stbi_image_free(data);
}

