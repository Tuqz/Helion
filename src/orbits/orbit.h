#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include "orbitable.h"

namespace helion {
	class Orbit {
	public:
		Orbit(const Orbitable &p, double semimajor = 0, double eccentricity = 0, double inclination = 0, double longitude = 0, double argument = 0, double time_of_periapsis = 0);
		//semimajor is as normal for ellipses, the periapsis distance for parabolas, and half the spacing between branchs of a hyperbola
		const double semimajor, eccentricity, inclination, long_asc_node, arg_of_periapsis, time_of_periapsis, period;
		const Orbitable &parent;
		glm::vec3 position(double theta) const;
	private:
		std::vector<glm::vec3> orbital_points; //Precalculated points for rendering purposes
		glm::vec3 get_position(double r, double theta) const;
		double altitude(double theta) const;
	};
}
