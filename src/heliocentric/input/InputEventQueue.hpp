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

/**
 * An input listener that puts all events into a queue to be processed later.
 * All listener functions return true, so this should be the last listener in 
 * the chain.
 */
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
	/**
	 * Return a pointer to the next event in the queue. 
	 * The pointer is valid until the next call to nextEvent.
	 * If the queue is empty, `nullptr` is returned.
	 * 
     * @return a pointer to the event at the front of the queue, or `nullptr` if
	 * the queue is empty
     */
	InputEvent* nextEvent();
	/**
	 * Removes all events from the queue. Consider calling this at the end of 
	 * each frame if your code does not process all events, to prevent the 
	 * memory taken up by these events to grow continually.
     */
	void clear();
};

#endif	/* INPUTEVENTQUEUE_HPP */

