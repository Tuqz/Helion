#pragma once
#include <vector>
#include <glm/vec3.hpp>

namespace helion {
	class CelestialBody;
	class Orbit {
	public:
		Orbit(CelestialBody &p, double semimajor = 0, double eccentricity = 0, double inclination = 0, double longitude = 0, double argument = 0, double time_of_periapsis = 0);
		//semimajor is as normal for ellipses, the periapsis distance for parabolas, and half the spacing between branchs of a hyperbola
		glm::vec3 position(double theta) const;
		double getSemimajor() const;
		double getEccentricity() const;
		double getInclination() const;
		double getLongitude() const;
		double getArgument() const;
		double getTimeOfPeriapsis() const;
		double getPeriod() const;
		CelestialBody& getParent() const;
		Orbit &operator=(const Orbit &o);
	private:
		CelestialBody &parent;
		double semimajor, eccentricity, inclination, long_asc_node, arg_of_periapsis, time_of_periapsis, period;
		std::vector<glm::vec3> orbital_points; //Precalculated points for rendering purposes

		glm::vec3 getPosition(double r, double theta) const;
		double altitude(double theta) const;
		void calculatePoints();
	};
}
