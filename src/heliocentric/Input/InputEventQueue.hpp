/* 
 * File:   InputEventPusher.hpp
 * Author: Ale Strooisma
 *
 * Created on August 4, 2015, 1:52 PM
 */

#ifndef INPUTEVENTQUEUE_HPP
#define	INPUTEVENTQUEUE_HPP

#include <queue>
#include "InputListener.hpp"
class InputEvent;

class InputEventQueue : public InputListener {
private:
	std::queue<InputEvent*> events;
	InputEvent* last = nullptr;
public:
	InputEventQueue();
	InputEventQueue(const InputEventQueue& orig);
	virtual ~InputEventQueue();
	virtual bool keyPressed(int key, int scancode, int mods, bool repeat);
	virtual bool keyReleased(int key, int scancode, int mods);
	virtual bool keyTyped(unsigned int codepoint);
	virtual bool mouseButtonPressed(int button, int mods);
	virtual bool mouseButtonReleased(int button, int mods);
	virtual bool mouseEnteredWindow();
	virtual bool mouseExitedWindow();
	virtual bool mouseMoved(double x, double y);
	virtual bool mouseWheelScrolled(double x, double y);
	InputEvent* nextEvent();
	void clear();
};

#endif	/* INPUTEVENTQUEUE_HPP */

