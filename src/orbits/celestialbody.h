#pragma once

#include <glm/vec3.hpp>

#include "orbitable.h"
#include "orbiter.h"
#include "orbit.h"

namespace helion {
	class CelestialBody : public Orbiter, public Orbitable {
	public:
		CelestialBody();
		CelestialBody(double mass, const Orbit &orbit);
		void update(double time);
		glm::vec3 position;
	};
}
