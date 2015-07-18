#pragma once
#include <glm/vec3.hpp>
#include "orbit.h"

class Orbiter { //Base class for anything that orbits
public:
	Orbit orbit;
	virtual void update(double time) = 0; //Do other stuff - should probably call orbit_update
	glm::vec3 position;
protected:
	void update_orbit(double time); //Move around orbit
	double anomaly;
};
