/* 
 * File:   InputListener.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 5:04 PM
 */

#ifndef INPUTLISTENER_HPP
#define	INPUTLISTENER_HPP

class InputListener {
public:
	virtual ~InputListener() {};
	virtual bool keyPressed(int key, int scancode, int mods, bool repeat) = 0;
	virtual bool keyReleased(int key, int scancode, int mods) = 0;
	virtual bool keyTyped(int codepoint) = 0;
	virtual bool mouseButtonPressed(int button, int mods) = 0;
	virtual bool mouseButtonReleased(int button, int mods) = 0;
	virtual bool mouseWheelScrolled(double x, double y) = 0;
	virtual bool mouseMoved(double x, double y) = 0;
	virtual bool mouseEnteredWindow() = 0;
	virtual bool mouseExitedWindow() = 0;
};

#endif	/* INPUTLISTENER_HPP */

