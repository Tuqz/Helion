#pragma once

#include "orbitable.h"
#include "orbiter.h"
#include "orbit.h"

class Planet : public Orbiter, public Orbitable {
public:
	Planet(double mass, const Orbit &orbit);
	void update(double time);
};
