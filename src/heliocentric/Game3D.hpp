/* 
 * File:   Game3D.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 7:33 PM
 */

#ifndef GAME3D_HPP
#define	GAME3D_HPP

#include "Game.hpp"
class GameInterface;

/**
 * An extension of Game for 3D games which adds a camera and scene graph.
 */
class Game3D : public Game {
private:
	GameInterface& game;
public:
	Game3D(GameInterface& gameInterface);
	virtual ~Game3D();
	// Game loop
	virtual void init();
	virtual void update(double dt);
	virtual void render();
	virtual void shutdown();
	virtual bool shouldStop();
private:

};

#endif	/* GAME3D_HPP */

