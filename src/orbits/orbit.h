#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include "orbitable.h"

class Orbit {
public:
	Orbit(double semimajor, double eccentricity, double inclination, double longitude, double argument, double time_of_periapsis, Orbitable *parent);
	Orbit();
	//semimajor is as normal for ellipses, the periapsis distance for parabolas, and half the spacing between branchs of a hyperbola
	double semimajor, eccentricity, inclination, long_asc_node, arg_of_periapsis, time_of_periapsis;
	double period();
	Orbitable *parent;
	glm::vec3 position(double theta);
private:
	std::vector<glm::vec3> orbital_points; //Precalculated points for rendering purposes
	glm::vec3 get_position(double r, double theta);
	double altitude(double theta);
};
