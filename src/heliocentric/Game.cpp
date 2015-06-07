/* 
 * File:   Game.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 7, 2015, 11:56 AM
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Game.hpp"
#include "Window.hpp"
#include "InputListener.hpp"

using namespace std;

void glfwErrorCallback(int error, const char* description) {
	cerr << "Error: " /*<< error << " - "*/ << description << endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Game* game = static_cast<Game*> (glfwGetWindowUserPointer(window));
	if (game->getInputListener()) {
		if (action == GLFW_PRESS) {
			game->getInputListener()->keyPressed(key, scancode, mods);
		} else if (action == GLFW_RELEASE) {
			game->getInputListener()->keyReleased(key, scancode, mods);
		} else {
			game->getInputListener()->keyRepeat(key, scancode, mods);
		}
	}
}

Game::Game() {
	// Initialize GLFW
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit()) {
		cerr << "Unable to initialize GLFW..." << endl;
		throw ERROR_GLFW_INIT;
	}

	// Create a window
	if (!window.create()) {
		cerr << "Unable to create GLFW window..." << endl;
		throw ERROR_GLFW_WINDOW;
	}
	
	// Initialize glew for the current context
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		cerr << "Unable to initialize GLEW..." << endl;
		throw ERROR_GLEW_INIT;
	}

	// Print OpenGL version
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	
	// Set up input handling
	glfwSetWindowUserPointer(window.getWindow(), this);
	glfwSetKeyCallback(window.getWindow(), keyCallback);
}

Game::~Game() {
	glfwTerminate();
}

void Game::run() {
	// Initialize FPS counter
	getDelta();
	prevCalcTime = getTime();

	// Allow user to initialize the game
	init();

	// Show the window
	window.show();

	// Enter the game loop
	while (!shouldStop()) {
		// Handle window resizing
		int w,h;
		window.getWindowSize(w, h);
		glViewport(0, 0, (GLsizei) w, (GLsizei) h);
		//resized();

		// Update the game state
		update(getDelta());
		//		getMousePosition(&prev_x, &prev_y);
		//		scroll_dx = 0;
		//		scroll_dy = 0;

		// Draw the next frame
		render();

		// Switch draw buffers
		glfwSwapBuffers(window.getWindow());

		// Update the FPS calculation
		updateFPS();
		glfwPollEvents();
	}

	// Allow user to clean up
	shutdown();
}

void Game::exit() {
	window.close();
}

void Game::init() {
}

void Game::update(double dt) {
}

void Game::render() {
}

void Game::shutdown() {
}

bool Game::shouldStop() {
	return glfwWindowShouldClose(window.getWindow());
}

Window& Game::getWindow() {
	return window;
}

InputListener* Game::getInputListener() {
	return inputListener;
}

void Game::setInputListener(InputListener* inputListener) {
	this->inputListener = inputListener;
}

double Game::getTime() {
	return glfwGetTime();
}

double Game::getDelta() {
	double time = getTime();
	double delta = time - prevTime;
	prevTime = time;

	return delta;
}

void Game::updateFPS() {
	if (getTime() - prevCalcTime > 1) {
		//glfwSetWindowTitle(window, (title + " (" + to_string(fps) + "FPS)").c_str());
		fps = 0;
		prevCalcTime += 1;
	}
	fps++;
}