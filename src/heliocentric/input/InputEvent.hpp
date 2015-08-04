/* 
 * File:   InputEvent.hpp
 * Author: Ale Strooisma
 *
 * Created on August 4, 2015, 1:04 PM
 */

#ifndef INPUTEVENT_HPP
#define	INPUTEVENT_HPP

enum class InputEventType {
	KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
	MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_WHEEL_SCROLLED,
	MOUSE_MOVED, MOUSE_ENTERED_WINDOW, MOUSE_EXITED_WINDOW
};

class InputEvent {
private:
	InputEventType type;
public:

	InputEvent(InputEventType type) : type(type) {
	}

	virtual ~InputEvent() {
	}

	InputEventType getType() const {
		return type;
	}

	virtual int getKey() {
		return -1;
	};

	virtual int getButton() {
		return -1;
	};

	virtual int getScancode() {
		return -1;
	};
	
	virtual int getMods() {
		return 0;
	};
	
	virtual unsigned int getCodepoint() {
		return 0;
	};
	
	virtual double getX() {
		return 0;
	}
	
	virtual double getY() {
		return 0;
	}

	bool isRepeat() const {
		return false;
	}
};

class KeyPressedEvent : public InputEvent {
private:
	int key;
	int scancode;
	int mods;
	bool repeat;
public:

	KeyPressedEvent(int key, int scancode, int mods, bool repeat)
	: InputEvent(InputEventType::KEY_PRESSED), key(key), scancode(scancode),
	mods(mods), repeat(repeat) {
	}

	virtual ~KeyPressedEvent() {
	}

	int getKey() const {
		return key;
	}

	int getMods() const {
		return mods;
	}

	bool isRepeat() const {
		return repeat;
	}

	int getScancode() const {
		return scancode;
	}
};

class KeyReleasedEvent : public InputEvent {
private:
	int key;
	int scancode;
	int mods;
public:

	KeyReleasedEvent(int key, int scancode, int mods)
	: InputEvent(InputEventType::KEY_RELEASED), key(key), scancode(scancode),
	mods(mods) {
	}

	virtual ~KeyReleasedEvent() {
	}

	int getKey() const {
		return key;
	}

	int getMods() const {
		return mods;
	}

	int getScancode() const {
		return scancode;
	}
};

class KeyTypedEvent : public InputEvent {
private:
	unsigned int codepoint;
public:

	KeyTypedEvent(unsigned int codepoint)
	: InputEvent(InputEventType::KEY_TYPED), codepoint(codepoint) {
	}

	virtual ~KeyTypedEvent() {
	}

	unsigned int getCodepoint() const {
		return codepoint;
	}
};

class MouseButtonPressedEvent : public InputEvent {
private:
	int button;
	int mods;
public:

	MouseButtonPressedEvent(int button, int mods)
	: InputEvent(InputEventType::MOUSE_BUTTON_PRESSED), button(button), mods(mods) {
	}

	virtual ~MouseButtonPressedEvent() {
	}

	int getButton() const {
		return button;
	}

	int getMods() const {
		return mods;
	}
};

class MouseButtonReleasedEvent : public InputEvent {
private:
	int button;
	int mods;
public:

	MouseButtonReleasedEvent(int button, int mods)
	: InputEvent(InputEventType::MOUSE_BUTTON_RELEASED), button(button), mods(mods) {
	}

	virtual ~MouseButtonReleasedEvent() {
	}

	int getButton() const {
		return button;
	}

	int getMods() const {
		return mods;
	}
};

class MouseWheelScrolledEvent : public InputEvent {
private:
	double x;
	double y;
public:

	MouseWheelScrolledEvent(double x, double y)
	: InputEvent(InputEventType::MOUSE_WHEEL_SCROLLED), x(x), y(y) {
	}

	virtual ~MouseWheelScrolledEvent() {
	}

	double getX() const {
		return x;
	}

	double getY() const {
		return y;
	}
};

class MouseMovedEvent : public InputEvent {
private:
	double x;
	double y;
public:

	MouseMovedEvent(double x, double y)
	: InputEvent(InputEventType::MOUSE_MOVED), x(x), y(y) {
	}

	virtual ~MouseMovedEvent() {
	}

	double getX() const {
		return x;
	}

	double getY() const {
		return y;
	}
};

class MouseEnteredWindowEvent : public InputEvent {
public:

	MouseEnteredWindowEvent()
	: InputEvent(InputEventType::MOUSE_ENTERED_WINDOW) {
	}

	virtual ~MouseEnteredWindowEvent() {
	}
};

class MouseExitedWindowEvent : public InputEvent {
public:

	MouseExitedWindowEvent()
	: InputEvent(InputEventType::MOUSE_EXITED_WINDOW) {
	}

	virtual ~MouseExitedWindowEvent() {
	}
};
#endif	/* INPUTEVENT_HPP */

