/* 
 * File:   OrbitingCameraModel.cpp
 * Author: Ale Strooisma
 * 
 * Created on August 7, 2015, 12:39 PM
 */

#include "GLFW/glfw3.h"
#include <glm/vec3.hpp>
#include <math.h>
#include "OrbitingCameraModel.hpp"
#include "CameraManager.hpp"
#include "Camera.hpp"
#include "../Game3D.hpp"
#include "../GameObject.hpp"

#define PI 3.14159265359

using namespace glm;

OrbitingCameraModel::OrbitingCameraModel() {
}

OrbitingCameraModel::OrbitingCameraModel(const OrbitingCameraModel& orig) {
}

OrbitingCameraModel::~OrbitingCameraModel() {
}

bool OrbitingCameraModel::set() {
	if (manager->getFocus() != nullptr) {
		return true;
	} else {
		return false;
	}
}

void OrbitingCameraModel::update(double dt) {
		manager->getCamera().resetOrientation();
		manager->getCamera().pan(pan);
		manager->getCamera().tilt(tilt);
		
		vec3 relpos(-sin(pan) * cos(tilt), -sin(tilt), cos(pan) * cos(tilt));
		manager->getCamera().setPosition(
		manager->getFocus()->getPosition() + relpos * distance);
}

bool OrbitingCameraModel::mouseEnteredWindow() {
	manager->getGame().getMousePosition(prevX, prevY);
}

bool OrbitingCameraModel::mouseButtonPressed(int button, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && mods == 0) {
		pantilt = true;
		manager->getGame().grabMouse();
		return true;
	}
}

bool OrbitingCameraModel::mouseButtonReleased(int button, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		pantilt = false;
		manager->getGame().releaseMouse();
		return true;
	}
}

bool OrbitingCameraModel::mouseMoved(double x, double y) {
	bool handled = false;
	if (pantilt) {
		pan = fmod(pan + (sensitivity * (x - prevX)), (2*PI));
		tilt = clamp(tilt + sensitivity * (prevY - y), -PI/2, PI/2);
		handled = true;
	}
	prevX = x;
	prevY = y;
	return handled;
}

bool OrbitingCameraModel::mouseWheelScrolled(double x, double y) {
	distance -= scrollspeed*y;
	if (distance < minDistance) {
		distance = minDistance;
	}
}
