#include "celestialbody.h"

using namespace helion;

CelestialBody::CelestialBody() :Orbitable(0), Orbiter(Orbit()) {
}

CelestialBody::CelestialBody(double m, const Orbit &o) : Orbitable(m), Orbiter(o) {
}

void CelestialBody::update(double time) {
	update_orbit(time);
}
