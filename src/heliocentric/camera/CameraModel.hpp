/* 
 * File:   CameraModel.hpp
 * Author: Ale Strooisma
 *
 * Created on August 6, 2015, 12:39 PM
 */

#ifndef CAMERAMODEL_HPP
#define	CAMERAMODEL_HPP

#include "../input/InputAdaptor.hpp"
#include "CameraManager.hpp"

class CameraModel : public InputAdaptor {
protected:
	CameraManager* manager;
public:
	CameraModel() {};
	CameraModel(const CameraModel& orig) {};
	virtual ~CameraModel() {};
	void setManager(CameraManager* manager) {
		this->manager = manager;
	}
	virtual bool set() = 0;
	virtual void update(double dt) = 0;
};

#endif	/* CAMERAMODEL_HPP */

