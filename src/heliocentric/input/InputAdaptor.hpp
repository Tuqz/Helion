/* 
 * File:   InputListener.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 5:04 PM
 */

#ifndef INPUTADAPTOR_HPP
#define	INPUTADAPTOR_HPP

#include "InputListener.hpp"

/**
 * Provides an empty implementation of `InputListener` for convenience. 
 * All functions return `false` without doing anything.
 */
class InputAdaptor : public InputListener {
public:

	virtual ~InputAdaptor() {
	};

	virtual bool keyPressed(int key, int scancode, int mods, bool repeat) {
		return false;
	};

	virtual bool keyReleased(int key, int scancode, int mods) {
		return false;
	};

	virtual bool keyTyped(unsigned int codepoint) {
		return false;
	};

	virtual bool mouseButtonPressed(int button, int mods) {
		return false;
	};

	virtual bool mouseButtonReleased(int button, int mods) {
		return false;
	};

	virtual bool mouseWheelScrolled(double x, double y) {
		return false;
	};

	virtual bool mouseMoved(double x, double y) {
		return false;
	};

	virtual bool mouseEnteredWindow() {
		return false;
	};

	virtual bool mouseExitedWindow() {
		return false;
	};
};

#endif	/* INPUTADAPTOR_HPP */

