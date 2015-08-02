/* 
 * File:   Game.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 7, 2015, 11:56 AM
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#include <chrono>
#include <thread>
#include <list>

#include "Game.hpp"
#include "Window.hpp"
#include "InputListener.hpp"
#include "exceptions.hpp"

using namespace std;

void glfwErrorCallback(int error, const char* description) {
	//cerr << "Error: " /*<< error << " - "*/ << description << endl;
	throw GLFWException(description);
}

void cb_windowClosed(GLFWwindow* window) {
	Game* wrapper = static_cast<Game*> (glfwGetWindowUserPointer(window));
	wrapper->windowClosed();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Game* game = static_cast<Game*> (glfwGetWindowUserPointer(window));
	if (action == GLFW_PRESS) {
		for (list<InputListener*>::iterator it = game->getInputListeners().begin();
				it != game->getInputListeners().end()
				&& !(*it)->keyPressed(key, scancode, mods, false); ++it);
	} else if (action == GLFW_RELEASE) {
		for (list<InputListener*>::iterator it = game->getInputListeners().begin();
				it != game->getInputListeners().end()
				&& !(*it)->keyReleased(key, scancode, mods); ++it);
	} else {
		for (list<InputListener*>::iterator it = game->getInputListeners().begin();
				it != game->getInputListeners().end()
				&& !(*it)->keyPressed(key, scancode, mods, true); ++it);
	}
}

Game::Game() {
	// Initialize GLFW
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit()) {
		throw GLFWException("Unable to initialize GLFW.");
	}

	// Create a window
	if (!window.create()) {
		throw GLFWException("Unable to create GLFW window.");
	}

	// Initialize glew for the current context
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		throw GLFWException("Unable to initialize GLEW...");
	}

	// Print OpenGL version
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	// Set up callback functions (for input handling)
	glfwSetWindowUserPointer(window.getWindow(), this);
	glfwSetKeyCallback(window.getWindow(), keyCallback);
	glfwSetWindowCloseCallback(window.getWindow(), cb_windowClosed);
}

Game::~Game() {
	glfwTerminate();
}

void Game::run() {
	try {
		// Initialize FPS counter
		double frameStartTime = getTime();
		prevFrameRateCalcTime = frameStartTime;

		// Prepare the framebuffer
		resized();

		// Allow user to initialize the game
		init();

		// Show the window
		window.show();

		// Enter the game loop
		while (!shouldStop()) {
			// Time management
			double time = getTime();
			double dt = time - frameStartTime;
			frameStartTime = time;

			// Get input events
			glfwPollEvents();

			// Update the game state
			update(dt);

			// Handle window resizing and draw the next frame
			int w, h;
			window.getWindowSize(w, h);
			glViewport(0, 0, (GLsizei) w, (GLsizei) h);
			resized();
			render();

			// Switch draw buffers
			glfwSwapBuffers(window.getWindow());

			// Update the FPS calculation
			updateFPS();

			// Wait until framelimit has been satisfied (for when vsync is disabled)
			if (frameTimeLimit - (getTime() - frameStartTime) > sleepLimit) {
				this_thread::sleep_for(chrono::microseconds(
						int(1000000 * (frameTimeLimit - (getTime() - frameStartTime) - sleepLimit))));
			}
			while (frameTimeLimit - (getTime() - frameStartTime) > 0) {
			}
		}
	} catch (const exception& e) {
		cerr << endl << "Stopping execution due to exception (" << typeid (e).name() << ") in game loop:" << endl;
		cerr << e.what() << endl;
	} catch (...) {
		cerr << endl << "Stopping execution due to unidentified exception in game loop." << endl;
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

void Game::resized() {
	int width, height;
	glfwGetWindowSize(window.getWindow(), &width, &height);
	windowResized(width, height);
}

void Game::windowResized(int width, int height) {
	glViewport(0, 0, width, height);
}

void Game::windowClosed() {
}

Window& Game::getWindow() {
	return window;
}

double Game::getTime() {
	return glfwGetTime();
}

void Game::updateFPS() {
	if (getTime() - prevFrameRateCalcTime > 1) {
		//glfwSetWindowTitle(window, (title + " (" + to_string(fps) + "FPS)").c_str());
		fps = fpsCounter;
		fpsCounter = 0;
		prevFrameRateCalcTime += 1;
	}
	fpsCounter++;
}

int Game::getFPS() {
	return fps;
}

void Game::addInputListener(InputListener* inputListener) {
	listeners.push_front(inputListener);
}

std::list<InputListener*>& Game::getInputListeners() {
	return listeners;
}

void Game::getMousePosition(double& x, double& y) {
	glfwGetCursorPos(window.getWindow(), &x, &y);
}

void Game::setMousePosition(double x, double y) {
	glfwSetCursorPos(window.getWindow(), x, y);
}

bool Game::isKeyPressed(int key) {
	return glfwGetKey(window.getWindow(), key) == GLFW_PRESS;
}

bool Game::isMouseButtonPressed(int button) {
	return glfwGetMouseButton(window.getWindow(), button) == GLFW_PRESS;
}
