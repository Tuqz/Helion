#pragma once
#include <unordered_map>
#include <string>
#include "celestialbody.h"
#include "orbitable.h"

namespace helion {
	typedef std::unordered_map<std::string, CelestialBody> SolarSystem;
	Orbitable loadSun(std::string filename);
	SolarSystem loadSystem(Orbitable *sun, std::string filename); //Load a solar system with sun as parent
}
