/* 
 * File:   OrbitingCameraModel.hpp
 * Author: Ale Strooisma
 *
 * Created on August 7, 2015, 12:39 PM
 */

#ifndef ORBITINGCAMERAMODEL_HPP
#define	ORBITINGCAMERAMODEL_HPP

#include "CameraModel.hpp"

class OrbitingCameraModel : public CameraModel {
public:
	OrbitingCameraModel();
	OrbitingCameraModel(const OrbitingCameraModel& orig);
	virtual ~OrbitingCameraModel();
	virtual bool set();
	virtual void update(double dt);
};

#endif	/* ORBITINGCAMERAMODEL_HPP */

