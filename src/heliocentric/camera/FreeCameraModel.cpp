/* 
 * File:   FreeCameraModel.cpp
 * Author: Ale Strooisma
 * 
 * Created on August 6, 2015, 12:40 PM
 */

#include "GLFW/glfw3.h"
#include "FreeCameraModel.hpp"
#include "CameraManager.hpp"
#include "Camera.hpp"
#include "../Game3D.hpp"

FreeCameraModel::FreeCameraModel() {
}

FreeCameraModel::FreeCameraModel(const FreeCameraModel& orig) {
}

FreeCameraModel::~FreeCameraModel() {
}

bool FreeCameraModel::set() {
	return true;
}

void FreeCameraModel::update(double dt) {
	manager->getCamera().moveRelative(movement*float(dt));
}

bool FreeCameraModel::mouseEnteredWindow() {
	manager->getGame().getMousePosition(prevX, prevY);
}

bool FreeCameraModel::mouseButtonPressed(int button, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && mods == 0) {
		pantilt = true;
		manager->getGame().grabMouse();
		return true;
	}
}

bool FreeCameraModel::mouseButtonReleased(int button, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		pantilt = false;
		manager->getGame().releaseMouse();
		return true;
	}
}

bool FreeCameraModel::mouseMoved(double x, double y) {
	bool handled = false;
	if (pantilt) {
		manager->getCamera().pan(sensitivity * (x - prevX));
		manager->getCamera().tilt(sensitivity * (prevY - y));
		handled = true;
	}
	prevX = x;
	prevY = y;
	return handled;
}

bool FreeCameraModel::keyPressed(int key, int scancode, int mods, bool repeat) {
	if (!repeat && mods == 0) {
		switch (key) {
			case GLFW_KEY_W:
				movement.z--;
				return true;
			case GLFW_KEY_S:
				movement.z++;
				return true;
			case GLFW_KEY_A:
				movement.x--;
				return true;
			case GLFW_KEY_D:
				movement.x++;
				return true;
			case GLFW_KEY_SPACE:
				movement.y++;
				return true;
			case GLFW_KEY_X:
				movement.y--;
				return true;
		}
	}
	return false;
}

bool FreeCameraModel::keyReleased(int key, int scancode, int mods) {
	switch (key) {
		case GLFW_KEY_W:
			movement.z++;
			return true;
		case GLFW_KEY_S:
			movement.z--;
			return true;
		case GLFW_KEY_A:
			movement.x++;
			return true;
		case GLFW_KEY_D:
			movement.x--;
			return true;
		case GLFW_KEY_SPACE:
			movement.y--;
			return true;
		case GLFW_KEY_X:
			movement.y++;
			return true;
	}
	return false;
}

