/* 
 * File:   Game3D.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 7, 2015, 7:33 PM
 */

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include "Game3D.hpp"
#include "GameInterface.hpp"
#include "util.hpp"

Game3D::Game3D(GameInterface& gameInterface) : game(gameInterface) {
}

Game3D::~Game3D() {
}

void Game3D::init() {
	// Enable face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Enable depth testing with clamping
    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    // Enable depth clamping if available (OpenGL 3.2)
    if (glversion(3, 2)) {
        glEnable(GL_DEPTH_CLAMP);
    }
	
	// Allow user to initialize the game
	game.init();
}

void Game3D::update(double dt) {
	game.update(dt);
}

void Game3D::render() {
	// Prepare drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Render the world
    glEnable(GL_DEPTH_TEST); // Making sure it is enabled
//    game.renderWorld(getCamera().getWorldToCameraMatrix());
    game.renderWorld(glm::mat4());
	
	// Render the HUD
    glDisable(GL_DEPTH_TEST); // Such that the HUD is rendered on top
    game.renderHUD(glm::mat4());
}

void Game3D::shutdown() {
	game.shutdown();
}

bool Game3D::shouldStop() {
	return Game::shouldStop() || game.shouldstop();
}
