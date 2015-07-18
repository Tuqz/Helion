#include "planet.h"

Planet::Planet(double m, const Orbit &o) : Orbitable(m), Orbiter() {
	orbit = o;
}

void Planet::update(double time) {
	update_orbit(time);
}
