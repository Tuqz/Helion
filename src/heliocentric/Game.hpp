/* 
 * File:   Game.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 11:56 AM
 */

#ifndef GAME_HPP
#define	GAME_HPP

#define ERROR_GLFW_INIT 1

#include "Window.hpp"

class InputListener;

/**
 * The central class of Heliocentric. Provides a game loop, delegates user input
 * and manages a window.
 */
class Game {
private:
	Window window;
	InputListener* inputListener;
	double prevTime, prevCalcTime;
	int fps;
public:
	Game();
	virtual ~Game();
	// Game loop
	void run();
	void exit();
	virtual void init();
	virtual void update(double dt);
	virtual void render();
	virtual void shutdown();
	virtual bool shouldStop();
	// Getters and setters
	Window& getWindow();
	InputListener* getInputListener();
	void setInputListener(InputListener* inputListener);
private:
	// Timing
	double getTime();
	double getDelta();
	void updateFPS();
};

#endif	/* GAME_HPP */

