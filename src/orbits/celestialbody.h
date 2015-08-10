#pragma once

#include "orbit.h"
#include "orbiter.h"
#include <glm/vec3.hpp>

namespace helion {
	class CelestialBody : public Orbiter {
	public:
		CelestialBody(double mass, const Orbit &orbit);
		void update(double time);
		double getMass();
		virtual glm::vec3 getPosition();
		double mu();
	private:
		double mass;
	};
}
