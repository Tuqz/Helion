/* 
 * File:   loaders.hpp
 * Author: Ale Strooisma
 *
 * Created on June 13, 2015, 12:20 PM
 */

#ifndef LOADERS_HPP
#define	LOADERS_HPP

class Mesh;

namespace loaders {
	Mesh* loadOBJ(std::string filename);
}

#endif	/* LOADERS_HPP */

