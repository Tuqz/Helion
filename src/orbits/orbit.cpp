#include "orbit.h"
#include <iostream>
#include <cmath>
#include "constants.h"
#include "celestialbody.h"

using namespace helion;

glm::vec3 Orbit::getPosition(double r, double theta) const {
			double angle_from_asc_node = theta + arg_of_periapsis;
			double x_tick = r * cos(angle_from_asc_node); //x_tick axis is parallel to line of asc. node
			double y_tick = r * sin(angle_from_asc_node); //y_tick is perp. to x_tick, and points above the plane
			double z_tick_tick = y_tick * cos(inclination);
			double y = y_tick * sin(inclination);
			double x = cos(long_asc_node)*x_tick + sin(long_asc_node)*z_tick_tick;
			double z = cos(long_asc_node)*z_tick_tick - sin(long_asc_node)*x_tick;
			return glm::vec3(x, y, z);
}

Orbit::Orbit(CelestialBody &p, double a, double e, double inc, double lan, double aop, double top)
	: parent(p), semimajor(a), eccentricity(e), inclination(inc), long_asc_node(lan), arg_of_periapsis(aop), time_of_periapsis(top) {
		period = 2*pi*sqrt(pow(std::abs(semimajor), 3)/p.mu()); //Reasonable only for ellipses, but the value is useful for other types
		calculatePoints();
}

void Orbit::calculatePoints() {
	orbital_points.clear();
	int points = 100;
	if(eccentricity < 1) { //Ellipse
		for(int i = 0; i < points; ++i) {
			double theta = i * (2 * M_PI/points);
			orbital_points.push_back(position(theta));
		}
	} else {
		if(eccentricity == 1) { //Parabola
			for(int i = 0; i < points; ++i) {
				double theta = (i - (points / 2) + 1) * (2 * M_PI/(points + 1)); 
				orbital_points.push_back(position(theta));
			}
		} else { //Hyperbola
			for(int i = 0; i < points; ++i ) {
				double crit_ang = acos(-1 / eccentricity);
				double theta = (i - (points / 2) + 1) * (2 * crit_ang /(points + 1));
				orbital_points.push_back(position(theta));
			}
		}
	}
}

glm::vec3 Orbit::position(double theta) const {
	return getPosition(altitude(theta), theta);
}

double Orbit::altitude(double theta) const {
	double l; //semi-latus rectum
	if(eccentricity	< 1) {
		l = semimajor*(1 - (eccentricity*eccentricity));
	} else {
		if(eccentricity == 1) {
			l = 2*semimajor;
		} else {
			l = semimajor*((eccentricity*eccentricity) - 1);
		}
	}
	return l/(1 + (eccentricity * cos(theta)));
}

double Orbit::getSemimajor() const {
	return semimajor;
}

double Orbit::getEccentricity() const {
	return eccentricity;
}

double Orbit::getInclination() const {
	return inclination;
}

double Orbit::getLongitude() const {
	return long_asc_node;
}

double Orbit::getArgument() const {
	return arg_of_periapsis;
}

double Orbit::getTimeOfPeriapsis() const {
	return time_of_periapsis;
}

double Orbit::getPeriod() const {
	return period;
}

CelestialBody& Orbit::getParent() const {
	return parent;
}

Orbit &Orbit::operator=(const Orbit &o) {
	parent = o.getParent();
	semimajor = o.getSemimajor();
	eccentricity = o.getEccentricity();
	inclination = o.getInclination();
	long_asc_node = o.getLongitude();
	arg_of_periapsis = o.getArgument();
	time_of_periapsis = o.getTimeOfPeriapsis();
	period = o.getPeriod();
	calculatePoints();
	return *this;
}
