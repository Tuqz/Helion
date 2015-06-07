/* 
 * File:   Window.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 7, 2015, 12:01 PM
 */

#include <GLFW/glfw3.h>
#include <string>

#include "Window.hpp"
#include "util.hpp"

Window::Window() {
}

Window::Window(const Window& orig) {
}

Window::~Window() {
}

//void Window::setWindow(GLFWwindow* window) {
//	this->window = window;
//}

GLFWwindow* Window::getWindow() {
	return window;
}

void Window::setTitle(std::string title) {
	this->title = title;
	glfwSetWindowTitle(window, title.c_str());
}

std::string Window::getTitle() {
	return title;
}

void Window::setWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
	glfwSetWindowSize(window, width, height);
}

void Window::getWindowSize(int& width, int& height) {
	width = this->width;
	height = this->height;
}

bool Window::create() {
	
	// Create the window
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) {
		return false;
	}
	
	// Enable OpenGL on this window
	glfwMakeContextCurrent(window);
	
	// Center the window on the screen
	int screenWidth, screenHeight;
	getCurrentResolution(&screenWidth, &screenHeight);
	glfwSetWindowPos(window, (screenWidth - width) / 2, (screenHeight - height) / 2);
	
	// Enable VSync
	glfwSwapInterval(1);
	
	return true;
}
