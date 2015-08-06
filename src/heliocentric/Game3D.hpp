/* 
 * File:   Game3D.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 7:33 PM
 */

#ifndef GAME3D_HPP
#define	GAME3D_HPP

#include "Game.hpp"
#include "camera/Camera.hpp"
#include "scenegraph/SceneGraph.hpp"
class GameInterface;

/**
 * An extension of Game for 3D games which adds a camera and scene graph.
 */
class Game3D : public Game {
private:
	GameInterface& game;
	Camera camera;
	SceneGraph scenegraph;
public:
	Game3D(GameInterface& gameInterface);
	virtual ~Game3D();
	// Game loop
	virtual void init();
	virtual void update(double dt);
	virtual void render();
	virtual void shutdown();
	virtual bool shouldStop();
	virtual void windowResized(int width, int height);
	virtual void windowClosed();
	// Getters
	Camera& getCamera();
	SceneGraph& getScenegraph();
private:

};

#endif	/* GAME3D_HPP */

