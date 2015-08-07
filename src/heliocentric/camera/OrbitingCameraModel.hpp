/* 
 * File:   OrbitingCameraModel.hpp
 * Author: Ale Strooisma
 *
 * Created on August 7, 2015, 12:39 PM
 */

#ifndef ORBITINGCAMERAMODEL_HPP
#define	ORBITINGCAMERAMODEL_HPP

#include "CameraModel.hpp"

/**
 * A camera model that makes the camera always point at a given object 
 * (specified by camera manager) and orbits around this object at a 
 * user-controlled distance.
 */
class OrbitingCameraModel : public CameraModel {
private:
	bool pantilt = false;
	double sensitivity = 0.005; // rad/pix
	float scrollspeed = 0.1;
	float distance = 1;
	float minDistance = 0.2;
	double prevX = 0, prevY = 0;
	float pan, tilt;
public:
	OrbitingCameraModel();
	OrbitingCameraModel(const OrbitingCameraModel& orig);
	virtual ~OrbitingCameraModel();
	virtual bool set();
	virtual void update(double dt);
	virtual bool mouseEnteredWindow();
	virtual bool mouseButtonPressed(int button, int mods);
	virtual bool mouseButtonReleased(int button, int mods);
	virtual bool mouseMoved(double x, double y);
	virtual bool mouseWheelScrolled(double x, double y);
};

#endif	/* ORBITINGCAMERAMODEL_HPP */

