#pragma once

#include "celestialbody.h"

namespace helion {
	class Star : public CelestialBody {
	public:
		Star(std::string n, double m) : CelestialBody(n, m, Orbit(*this)) {
		}

		glm::vec3 getPosition() {
			return glm::vec3(0, 0, 0);
		}
		
		void update(double time) {
			//Do nothing - stars shouldn't move!
		}
	};
}
