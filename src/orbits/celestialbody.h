#pragma once

#include "orbitable.h"
#include "orbiter.h"
#include "orbit.h"

namespace helion {
	class CelestialBody : public Orbiter, public Orbitable {
	public:
		CelestialBody(double mass, const Orbit &orbit);
		void update(double time);
	};
}
