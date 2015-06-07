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
	virtual void keyPressed(int key, int scancode, int mods) = 0;
	virtual void keyRepeat(int key, int scancode, int mods) = 0;
	virtual void keyReleased(int key, int scancode, int mods) = 0;
};

#endif	/* INPUTLISTENER_HPP */

