#pragma once
#include <glm/vec3.hpp>
#include "orbit.h"

namespace helion {
	class Orbiter { //Base class for anything that orbits
	public:
		Orbiter(const Orbit &o);
		Orbit orbit;
		virtual void update(double time) = 0; //Do other stuff - should probably call orbit_update
		glm::vec3 getPosition();
	protected:
		void update_orbit(double time); //Move around orbit
		double anomaly;
	};
}
