#include "celestialbody.h"
#include "constants.h"

using namespace helion;

CelestialBody::CelestialBody() : Orbiter(Orbit(*this)) {
	name = "";
	mass = 0;
}

CelestialBody::CelestialBody(std::string n, double m, const Orbit &o) : Orbiter(o) { 
	name = n;
	mass = m;
}

CelestialBody::~CelestialBody() {
}

void CelestialBody::update(double time) {
	update_orbit(time);
}

double CelestialBody::mu() const {
	return G * mass;
}

glm::vec3 CelestialBody::getPosition() const {
	return orbit.position(anomaly) + orbit.getParent().getPosition();
}

void CelestialBody::addChild(std::shared_ptr<CelestialBody> child) {
	children.push_back(child);
}

void CelestialBody::apply(CelestialFunction &func) {
	func.call(this);
	for(auto it = children.begin(); it != children.end(); ++it) {
		(*it)->apply(func);
	}
}
