#include "celestialbody.h"
#include "constants.h"

using namespace helion;

CelestialBody::CelestialBody(double m, const Orbit &o) : Orbiter(o) { 
	mass = m;
}

void CelestialBody::update(double time) {
	update_orbit(time);
}

double CelestialBody::getMass() {
	return mass;
}

double CelestialBody::mu() {
	return G * mass;
}

glm::vec3 CelestialBody::getPosition() {
	return orbit.position(anomaly) + orbit.getParent().getPosition();
}
