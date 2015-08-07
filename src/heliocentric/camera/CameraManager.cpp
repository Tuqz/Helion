/* 
 * File:   CameraManager.cpp
 * Author: Ale Strooisma
 * 
 * Created on August 4, 2015, 8:37 PM
 */


#include "CameraManager.hpp"
#include "../Game3D.hpp"
#include "Camera.hpp"
#include "FreeCameraModel.hpp"
#include "../exceptions.hpp"

using namespace std;

CameraManager::CameraManager(Game3D& game) : CameraManager(game, game.getCamera()) {
}

CameraManager::CameraManager(Game3D& game, Camera& camera) : game(game), camera(camera), currentIterator(models.end()) {
	if (!addModel("free", &fcm)) {
		throw Exception("Unable to initialize camera manager: failed to add free camera model.");
	}
	if (!setModel("free")) {
		throw Exception("Unable to initialize camera manager: failed to select free camera model.");
	}
	if (currentIterator == models.end()) {
		throw Exception("Unable to initialize camera manager.");
	}
}

CameraManager::CameraManager(const CameraManager& orig) : CameraManager(orig.game, orig.camera) {
}

CameraManager::~CameraManager() {
}

bool CameraManager::addModel(std::string label, CameraModel* model) {
	pair < map<string, CameraModel*>::iterator, bool> res = models.insert(pair<string, CameraModel*>(label, model));
	if (res.second) {
		model->manager = this;
	}
	return res.second;
}

bool CameraManager::setModel(std::string label) {
	return set(models.find(label));
}

bool CameraManager::nextModel() {
	std::map<std::string, CameraModel*>::iterator it = next(currentIterator);
	if (it == models.end()) {
		it = models.begin();
	}
	return set(it);
}

bool CameraManager::set(std::map<std::string, CameraModel*>::iterator it) {
	if (it != models.end() && it->second->set()) {
		currentIterator = it;
		return true;
	} else {
		return false;
	}
}

void CameraManager::update(double dt) {
	return getCurrentModel()->update(dt);
}

bool CameraManager::keyPressed(int key, int scancode, int mods, bool repeat) {
	return getCurrentModel()->keyPressed(key, scancode, mods, repeat);
}

bool CameraManager::keyReleased(int key, int scancode, int mods) {
	return getCurrentModel()->keyReleased(key, scancode, mods);
}

bool CameraManager::keyTyped(unsigned int codepoint) {
	return getCurrentModel()->keyTyped(codepoint);
}

bool CameraManager::mouseButtonPressed(int button, int mods) {
	return getCurrentModel()->mouseButtonPressed(button, mods);
}

bool CameraManager::mouseButtonReleased(int button, int mods) {
	return getCurrentModel()->mouseButtonReleased(button, mods);
}

bool CameraManager::mouseWheelScrolled(double x, double y) {
	return getCurrentModel()->mouseWheelScrolled(x, y);
}

bool CameraManager::mouseMoved(double x, double y) {
	return getCurrentModel()->mouseMoved(x, y);
}

bool CameraManager::mouseEnteredWindow() {
	return getCurrentModel()->mouseEnteredWindow();
}

bool CameraManager::mouseExitedWindow() {
	return getCurrentModel()->mouseExitedWindow();
}