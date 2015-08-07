/* 
 * File:   CameraModel.hpp
 * Author: Ale Strooisma
 *
 * Created on August 6, 2015, 12:39 PM
 */

#ifndef CAMERAMODEL_HPP
#define	CAMERAMODEL_HPP

#include "../input/InputAdaptor.hpp"
//#include "CameraManager.hpp"
class CameraManager;

/**
 * An interface for specifying camera controls.
 */
class CameraModel : public InputAdaptor {
	friend class CameraManager;
protected:
	CameraManager* manager;
public:
	CameraModel() {};
	CameraModel(const CameraModel& orig) {};
	virtual ~CameraModel() {};
	/**
	 * Called by `CameraManager` when the model is selected, to initialize the 
	 * camera state if needed. If initialization fails, return `false`, so that 
	 * the model does not get set.
	 * 
     * @return true if initialization was successful
     */
	virtual bool set() = 0;
	/**
	 * Called by `CameraManager` each frame to allow a timestep-based update to 
	 * the camera.
	 */
	virtual void update(double dt) = 0;
};

#endif	/* CAMERAMODEL_HPP */

