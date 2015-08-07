/* 
 * File:   InputListener.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 5:04 PM
 */

#ifndef INPUTLISTENER_HPP
#define	INPUTLISTENER_HPP

/**
 * An interface for defining input listeners.
 * The specified functions are called to handle events, just before the update 
 * function.
 * All functions must return a boolean value. If this value is true, the event 
 * is considered handled and will not be passed to subsequent listeners.
 */
class InputListener {
public:
	virtual ~InputListener() {};
	/**
	 * Called when a key is pressed. It is also called for key repeat events 
	 * when the key is held down (OS-dependent). In this key the parameter 
	 * `repeat` will be true.
	 * 
	 * Do not use this for text, because this function does not consider
	 * keyboard layouts. Instead use `keyTyped` for this, which is called
	 * additionally whenever a key event can be interpreted as a UTF-8 character.
	 * Note that there are no guarantees on the order in which this function and
	 * `keyTyped` are called.
	 * 
	 * The parameter `key` is a key token, 
	 * [as defined by GLFW](http://www.glfw.org/docs/latest/group__keys.html).
	 * The scancode is unique for every key, regardless of whether it has a key 
	 * token. Scancodes are platform-specific but consistent over time, so keys 
	 * will have different scancodes depending on the platform but they are safe 
	 * to save to disk. The modifier keys that were held down at the time of the 
	 * keypress are given by a bitwise OR of the macros `GLFW_MOD_SHIFT`, 
	 * `GLFW_MOD_CONTROL`, `GLFW_MOD_ALT` and `GLFW_MOD_SUPER`. In the future 
	 * more user-friendly alternatives for the GLFW-macros will be provided.
	 * 
     * @param key key token representing which key is pressed
     * @param scancode platform-specific representation of the pressed key
     * @param mods bitwise OR-ed values representing the modifier keys held down
	 * at the time of the keypress
     * @param repeat true if the event is due to key-repeat, contrary to a true 
	 * key pressed event
     * @return true if the event is handled
     */
	virtual bool keyPressed(int key, int scancode, int mods, bool repeat) = 0;
	/**
	 * Called when a key is released.
	 * 
	 * The parameter `key` is a key token, 
	 * [as defined by GLFW](http://www.glfw.org/docs/latest/group__keys.html).
	 * The scancode is unique for every key, regardless of whether it has a key 
	 * token. Scancodes are platform-specific but consistent over time, so keys 
	 * will have different scancodes depending on the platform but they are safe 
	 * to save to disk. The modifier keys that were held down at the time of the 
	 * release are given by a bitwise OR of the macros `GLFW_MOD_SHIFT`, 
	 * `GLFW_MOD_CONTROL`, `GLFW_MOD_ALT` and `GLFW_MOD_SUPER`. In the future 
	 * more user-friendly alternatives for the GLFW-macros will be provided.
	 * 
     * @param key key token representing which key was released
     * @param scancode platform-specific representation of the released key
     * @param mods bitwise OR-ed values representing the modifier keys held down
	 * at the time of the release
     * @return true if the event is handled
     */
	virtual bool keyReleased(int key, int scancode, int mods) = 0;
	/**
	 * If a keypress generates a UTF-8 compatible character, this function is 
	 * called. This function is meant solely for handling text input. It takes
	 * keyboard layout into account and supports dead keys. The character 
	 * depends on modifiers. This function will not be called if the combination
	 * of the key pressed and the modifier keys held down does not produce a 
	 * UTF-8 compatible character (for example, CTRL+A).
	 * 
	 * Because an unsigned int is 32 bits long on all supported platforms, you 
	 * can treat the code point argument as native endian UTF-32.
	 * 
	 * Note that there are no guarantees on the order in which this function and
	 * `keyPressed` are called.
	 * 
     * @param codepoint the UTF-8 encoding of the generated character
     * @return true if the event is handled
     */
	virtual bool keyTyped(unsigned int codepoint) = 0;
	/**
	 * Called whenever a mouse button is pressed.
	 * 
	 * The parameter `button` can be interpreted using the 
	 * [macros specified by GLFW](http://www.glfw.org/docs/latest/group__buttons.html).
	 * 
     * @param button the pressed button
	 * @param mods bitwise OR-ed values representing the modifier keys held down
	 * at the time of the button press
     * @return true if the event is handled
     */
	virtual bool mouseButtonPressed(int button, int mods) = 0;
	/**
	 * Called whenever a mouse button is released.
	 * 
	 * The parameter `button` can be interpreted using the 
	 * [macros specified by GLFW](http://www.glfw.org/docs/latest/group__buttons.html).
	 * 
     * @param button the released button
	 * @param mods bitwise OR-ed values representing the modifier keys held down
	 * at the time of the button release
     * @return true if the event is handled
     */
	virtual bool mouseButtonReleased(int button, int mods) = 0;
	/**
	 * Called when the mouse wheel is scrolled.
	 * Two-dimensional scrolling amounts are given.
	 * Regular mouses only scroll in the y-direction.
	 * 
     * @param x the amount scrolled in the x-direction
     * @param y the amount scrolled in the y-direction
     * @return true if the event is handled
     */
	virtual bool mouseWheelScrolled(double x, double y) = 0;
	/**
	 * Gives the position of the mouse cursor every time it moves over the window.
	 * 
     * @param x the x-position
     * @param y the y-position
     * @return true if the event is handled
     */
	virtual bool mouseMoved(double x, double y) = 0;
	/**
	 * Called when the mouse cursor enters the window. Note that it is also 
	 * called when the mouse is over the window when the window appears.
	 * 
     * @return true if the event is handled
     */
	virtual bool mouseEnteredWindow() = 0;
	/**
	 * Called when the mouse cursor leaves the window.
	 * 
     * @return true if the event is handled
     */
	virtual bool mouseExitedWindow() = 0;
};

#endif	/* INPUTLISTENER_HPP */

