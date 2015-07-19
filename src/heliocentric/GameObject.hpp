/* 
 * File:   GameObject.hpp
 * Author: Ale Strooisma
 *
 * Created on July 19, 2015, 3:37 PM
 */

#ifndef GAMEOBJECT_HPP
#define	GAMEOBJECT_HPP

#include <glm/fwd.hpp>

class GameObject {
public:
	virtual ~GameObject() {};
	virtual glm::vec3 getPosition() = 0;
	virtual glm::quat getOrientation() = 0;
};

#endif	/* GAMEOBJECT_HPP */

