/* 
 * File:   Game.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 7, 2015, 11:56 AM
 */

#include <GLFW/glfw3.h>
#include <iostream>

#include "Game.hpp"
#include "Window.hpp"

using namespace std;

void glfwErrorCallback(int error, const char* description) {
	cerr << "Error: " /*<< error << " - "*/ << description << endl;
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
		throw ERROR_GLFW_INIT;
	}
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
	
	while (!glfwWindowShouldClose(window.getWindow())) {
//	while (!shouldStop()) {
		// Handle window resizing
		//resized();

		// Update the game state
		glfwPollEvents();
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

Window& Game::getWindow() {
	return window;
}
