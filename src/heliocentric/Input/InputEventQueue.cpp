/* 
 * File:   InputEventPusher.cpp
 * Author: Ale Strooisma
 * 
 * Created on August 4, 2015, 1:52 PM
 */

#include <queue>

#include "InputEventQueue.hpp"
#include "InputEvent.hpp"

using namespace std;

InputEventQueue::InputEventQueue() {
}

InputEventQueue::InputEventQueue(const InputEventQueue& orig) {
}

InputEventQueue::~InputEventQueue() {
	clear();
}

InputEvent* InputEventQueue::nextEvent() {
	delete last;
	if (events.empty()) {
		last = nullptr;
	} else {
		last = events.front();
		events.pop();
	}
	return last;
}

void InputEventQueue::clear() {
	while (!events.empty()) {
		delete events.front();
		events.pop();
	}
}

bool InputEventQueue::keyPressed(int key, int scancode, int mods, bool repeat) {
	events.push(new KeyPressedEvent(key, scancode, mods, repeat));
	return true;
}

bool InputEventQueue::keyReleased(int key, int scancode, int mods) {
	events.push(new KeyReleasedEvent(key, scancode, mods));
	return true;
}

bool InputEventQueue::keyTyped(unsigned int codepoint) {
	events.push(new KeyTypedEvent(codepoint));
	return true;
}

bool InputEventQueue::mouseButtonPressed(int button, int mods) {
	events.push(new MouseButtonPressedEvent(button, mods));
	return true;
}

bool InputEventQueue::mouseButtonReleased(int button, int mods) {
	events.push(new MouseButtonReleasedEvent(button, mods));
	return true;
}

bool InputEventQueue::mouseEnteredWindow() {
	events.push(new MouseEnteredWindowEvent());
	return true;
}

bool InputEventQueue::mouseExitedWindow() {
	events.push(new MouseExitedWindowEvent());
	return true;
}

bool InputEventQueue::mouseMoved(double x, double y) {
	events.push(new MouseMovedEvent(x, y));
	return true;
}

bool InputEventQueue::mouseWheelScrolled(double x, double y) {
	events.push(new MouseWheelScrolledEvent(x, y));
	return true;
}
