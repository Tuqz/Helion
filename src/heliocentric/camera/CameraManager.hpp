/* 
 * File:   CameraManager.hpp
 * Author: Ale Strooisma
 *
 * Created on August 4, 2015, 8:37 PM
 */

#ifndef CAMERAMANAGER_HPP
#define	CAMERAMANAGER_HPP

#include <map>
#include <string>
#include "../input/InputListener.hpp"
class Game3D;
class Camera;
class CameraModel;

class CameraManager : public InputListener {
private:
	Game3D& game;
	Camera& camera;
	std::map<std::string, CameraModel*> models;
	CameraModel* currentModel;
public:
	CameraManager(Game3D& game, Camera& camera);
	CameraManager(const CameraManager& orig);
	virtual ~CameraManager();
	bool addModel(std::string label, CameraModel* model);
	bool setModel(std::string label);
	void update(double dt);
	virtual bool keyPressed(int key, int scancode, int mods, bool repeat);
	virtual bool keyReleased(int key, int scancode, int mods);
	virtual bool keyTyped(unsigned int codepoint);
	virtual bool mouseButtonPressed(int button, int mods);
	virtual bool mouseButtonReleased(int button, int mods);
	virtual bool mouseWheelScrolled(double x, double y);
	virtual bool mouseMoved(double x, double y);
	virtual bool mouseEnteredWindow();
	virtual bool mouseExitedWindow();
	Game3D& getGame() const {
		return game;
	}
	Camera& getCamera() const {
		return camera;
	}
};

#endif	/* CAMERAMANAGER_HPP */

