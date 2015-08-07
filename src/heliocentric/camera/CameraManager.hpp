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
#include "FreeCameraModel.hpp"
class GameObject;
class Game3D;
class Camera;
class CameraModel;

/**
 * A tool for switching between different camera control models, e.g. a free 
 * camera or a chase camera. Those models are defined by implementing the 
 * `CameraModel` interface.
 * 
 * After creation, the camera manager has to be added as an input listener.
 * It should most likely process events before the game's main input handler and 
 * after the GUI.
 * 
 * Additionally, `CameraManager::update` needs to be called each frame. Most
 * likely it is the last call in the `update` function of your `GameInterface` 
 * implementation.
 */
class CameraManager : public InputListener {
private:
	Game3D& game;
	Camera& camera;
	FreeCameraModel fcm;
	std::map<std::string, CameraModel*> models;
	std::map<std::string, CameraModel*>::iterator currentIterator;
	GameObject* focus = nullptr;
public:
	/**
	 * Creates a new `CameraManager` that controls the default camera.
	 * The current game is required to allow polling in the camera models.
	 * A free camera model is added under the label "free".
	 * After creation, the camera manager has to be added as an input listener.
	 * 
     * @param game the current game
     */
	CameraManager(Game3D& game);
	/**
	 * Creates a new `CameraManager` that controls the given camera.
	 * The current game is required to allow polling in the camera models.
	 * A free camera model is added under the label "free".
	 * After creation, the camera manager has to be added as an input listener.
	 * 
     * @param game the current game
     * @param camera the camera to control
     */
	CameraManager(Game3D& game, Camera& camera);
	CameraManager(const CameraManager& orig);
	virtual ~CameraManager();
	/**
	 * Adds the given model. When successful, the model can be selected using the
	 * given label. If adding the model fails, `false` is returned.
	 * 
     * @param label the label under which to add the model
     * @param model the camera model to add
     * @return true if successful
     */
	bool addModel(std::string label, CameraModel* model);
	/**
	 * Select the model that was added with the given label.
	 * If this fails, for example due to an nonexistent label being passed,
	 * `false` is returned and the previous model remains set.
	 * 
     * @param label the label belonging to the model to select
     * @return true if successful
     */
	bool setModel(std::string label);
	/**
	 * Selects the next camera model. 
	 * Note that the only guarantee about the order of the models is that the 
	 * order remains constant as long as no models are added.
	 * If setting the next model fails, `false` is returned and the current 
	 * model remains set, as in `setModel`.
	 * 
	 * @return true if successful
     */
	bool nextModel();
	/**
	 * This method calls the update method of the currently set model, and 
	 * should therefore be called in the update method of your GameInterface
	 * implementation.
	 * 
     * @param dt the time since the last update call, in seconds
     */
	void update(double dt);
	/**
	 * Set the object that the camera focuses on. Only some camera models 
	 * require a focus object. The free camera for example does not.
     * @param obj the object to focus on
     */
	void focusOn(GameObject* obj) {
		focus = obj;
	}
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
	std::string getCurrentModelLabel() {
		return currentIterator->first;
	}
	CameraModel* getCurrentModel() {
		return currentIterator->second;
	}
	GameObject* getFocus() const {
		return focus;
	}
private:
	bool set(std::map<std::string, CameraModel*>::iterator it);
};

#endif	/* CAMERAMANAGER_HPP */

