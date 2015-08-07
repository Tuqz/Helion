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

CameraManager::CameraManager(Game3D& game, Camera& camera) : game(game), camera(camera) {
	CameraModel* freecam = new FreeCameraModel();
	if (!addModel("free", freecam)) {
		throw Exception("Unable to initialize camera manager: failed to add free camera model.");
	}
	if (!setModel("free")) {
		throw Exception("Unable to initialize camera manager: failed to select free camera model.");
	}
	if (currentModel == nullptr) {
		throw Exception("Unable to initialize camera manager.");
	}
}

CameraManager::CameraManager(const CameraManager& orig) : CameraManager(orig.game, orig.camera) {
}

CameraManager::~CameraManager() {
	for (map<string, CameraModel*>::iterator it = models.begin(); it != models.end(); ++it) {
		delete it->second;
	}
}

bool CameraManager::addModel(std::string label, CameraModel* model) {
	pair < map<string, CameraModel*>::iterator, bool> res = models.insert(pair<string, CameraModel*>(label, model));
	if (res.second) {
		model->manager = this;
	}
	return res.second;
}

bool CameraManager::setModel(std::string label) {
	map<string, CameraModel*>::iterator it = models.find(label);
	if (it != models.end() && it->second->set()) {
		currentModel = it->second;
		return true;
	} else {
		return false;
	}
}

void CameraManager::update(double dt) {
	return currentModel->update(dt);
}

bool CameraManager::keyPressed(int key, int scancode, int mods, bool repeat) {
	return currentModel->keyPressed(key, scancode, mods, repeat);
}

bool CameraManager::keyReleased(int key, int scancode, int mods) {
	return currentModel->keyReleased(key, scancode, mods);
}

bool CameraManager::keyTyped(unsigned int codepoint) {
	return currentModel->keyTyped(codepoint);
}

bool CameraManager::mouseButtonPressed(int button, int mods) {
	return currentModel->mouseButtonPressed(button, mods);
}

bool CameraManager::mouseButtonReleased(int button, int mods) {
	return currentModel->mouseButtonReleased(button, mods);
}

bool CameraManager::mouseWheelScrolled(double x, double y) {
	return currentModel->mouseWheelScrolled(x, y);
}

bool CameraManager::mouseMoved(double x, double y) {
	return currentModel->mouseMoved(x, y);
}

bool CameraManager::mouseEnteredWindow() {
	return currentModel->mouseEnteredWindow();
}

bool CameraManager::mouseExitedWindow() {
	return currentModel->mouseExitedWindow();
}