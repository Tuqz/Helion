#pragma once

#include <unordered_map>
#include <string>
#include "celestialbody.h"

namespace helion {
	class SolarSystem {
	public:
		SolarSystem(const std::string &filename);
		void update_celestial_bodies(double time);
		void addBody(std::string name, CelestialBody &body);
		void addBody(std::string name, CelestialBody &&body);
		CelestialBody &getBody(std::string name);
	private:
		std::unordered_map<std::string, CelestialBody> system;
	};
}
