/* 
 * File:   FreeCameraModel.hpp
 * Author: Ale Strooisma
 *
 * Created on August 6, 2015, 12:40 PM
 */

#ifndef FREECAMERAMODEL_HPP
#define	FREECAMERAMODEL_HPP

#include "CameraModel.hpp"
#include <glm/vec3.hpp>

/**
 * Camera model for a free camera.
 */
class FreeCameraModel : public CameraModel {
private:
	bool pantilt = false;
	double sensitivity = 0.005; // rad/pix
	double prevX = 0, prevY = 0;
	glm::vec3 movement;
public:
	FreeCameraModel();
	FreeCameraModel(const FreeCameraModel& orig);
	virtual ~FreeCameraModel();
	virtual bool set();
	virtual void update(double dt);
	virtual bool mouseEnteredWindow();
	virtual bool mouseButtonPressed(int button, int mods);
	virtual bool mouseButtonReleased(int button, int mods);
	virtual bool mouseMoved(double x, double y);
	virtual bool keyPressed(int key, int scancode, int mods, bool repeat);
	virtual bool keyReleased(int key, int scancode, int mods);
};

#endif	/* FREECAMERAMODEL_HPP */

