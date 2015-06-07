/* 
 * File:   main.cpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 12:38 PM
 */

#include <cstdlib>
#include <iostream>

#include "heliocentric/Game.hpp"

using namespace std;

/*
 * Boots Helion
 */
int main(int argc, char** argv) {
	Game game;
	game.run();
	return 0;
}

