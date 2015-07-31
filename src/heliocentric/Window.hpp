/* 
 * File:   Window.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 12:01 PM
 */

#ifndef WINDOW_HPP
#define	WINDOW_HPP

#include <string>

struct GLFWwindow;

/**
 * A wrapper class for the GLFW window.
 */
class Window {
	friend class Game;
private:
	GLFWwindow* window;
	std::string title = "Heliocentric";
	int width = 640, height = 480;
public:
	Window();
	Window(const Window& orig);
	virtual ~Window();
	GLFWwindow* getWindow();
	void setTitle(std::string title);
	std::string getTitle();
	void setWindowSize(int width, int height);
	void getWindowSize(int& width, int& height);
	void close(bool close = true);
private:
	bool create();
	void show();
};

#endif	/* WINDOW_HPP */

