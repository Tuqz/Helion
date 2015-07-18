#include "orbit.h"
#include <iostream>
#include <cmath>
#include "constants.h"

glm::vec3 Orbit::get_position(double r, double theta) const {
			double angle_from_asc_node = theta + arg_of_periapsis;
			double x_tick = r * cos(angle_from_asc_node); //x_tick axis is parallel to line of asc. node
			double y_tick = r * sin(angle_from_asc_node); //y_tick is perp. to x_tick, and points above the plane
			double z_tick_tick = y_tick * cos(inclination);
			double y = y_tick * sin(inclination);
			double x = cos(long_asc_node)*x_tick + sin(long_asc_node)*z_tick_tick;
			double z = cos(long_asc_node)*z_tick_tick - sin(long_asc_node)*x_tick;
			return glm::vec3(x, y, z);
}

Orbit::Orbit() : semimajor(0), eccentricity(0), inclination(0), long_asc_node(0), arg_of_periapsis(0), time_of_periapsis(0), period(0) {
	parent = nullptr;
}

Orbit::Orbit(double a, double e, double inc, double lan, double aop, double top, Orbitable *p) : semimajor(a), eccentricity(e), inclination(inc), long_asc_node(lan), arg_of_periapsis(aop), time_of_periapsis(top), period(2*pi*sqrt(pow(std::abs(semimajor), 3)/p->mu)) {
	parent = p;
	int points = 100;
	if(e < 1) { //Ellipse
		for(int i = 0; i < points; ++i) {
			double theta = i * (2 * M_PI/points);
			orbital_points.push_back(position(theta));
		}
	} else {
		if(e == 1) { //Parabola
			for(int i = 0; i < points; ++i) {
				double theta = (i - (points / 2) + 1) * (2 * M_PI/(points + 1)); 
				orbital_points.push_back(position(theta));
			}
		} else { //Hyperbola
			for(int i = 0; i < points; ++i ) {
				double crit_ang = acos(-1 / e);
				double theta = (i - (points / 2) + 1) * (2 * crit_ang /(points + 1));
				orbital_points.push_back(position(theta));
			}
		}
	}
}

glm::vec3 Orbit::position(double theta) const {
	return get_position(altitude(theta), theta);
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
