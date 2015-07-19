/* 
 * File:   Game.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 11:56 AM
 */

#ifndef GAME_HPP
#define	GAME_HPP

#define ERROR_GLFW_INIT 1
#define ERROR_GLFW_WINDOW 2
#define ERROR_GLEW_INIT 3

#include "Window.hpp"

class InputListener;

/**
 * The central class of Heliocentric. Provides a game loop, delegates user input
 * and manages a window.
 */
class Game {
private:
	Window window;
	InputListener* inputListener = nullptr;
	double prevFrameRateCalcTime;
	int fpsCounter = 0, fps = 0;
	double frameTimeLimit = 1.0/120.0;
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
	int getFPS();
private:
	// Timing
	double getTime();
	void updateFPS();
};

#endif	/* GAME_HPP */

