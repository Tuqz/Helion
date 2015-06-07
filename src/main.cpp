/* 
 * File:   main.cpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 12:38 PM
 */

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

#include "heliocentric/Game.hpp"
#include "heliocentric/InputListener.hpp"

using namespace std;

class Input : public InputListener {
private:
	Game& game;
public:
	Input(Game& game) : game(game) {};
	
	virtual void keyPressed(int key, int scancode, int mods) {
		if (key == GLFW_KEY_ESCAPE) {
			game.exit();
		}
	}

	virtual void keyReleased(int key, int scancode, int mods) {
	}

	virtual void keyRepeat(int key, int scancode, int mods) {
	}
};

/*
 * Boots Helion
 */
int main(int argc, char** argv) {
	Game game;
	game.run();
	return 0;
}

