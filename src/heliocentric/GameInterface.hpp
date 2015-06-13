/* 
 * File:   GameInterface.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 7:53 PM
 */

#ifndef GAMEINTERFACE_HPP
#define	GAMEINTERFACE_HPP

#include <glm/mat4x4.hpp>

class Game3D;

class GameInterface {
public:
	virtual ~GameInterface() {};
	virtual void setGame(Game3D* game) = 0;
	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void renderWorld(glm::mat4 base) = 0;
	virtual void renderHUD(glm::mat4 base) = 0;
	virtual void shutdown() = 0;
	virtual bool shouldstop() = 0;
};

#endif	/* GAMEINTERFACE_HPP */

