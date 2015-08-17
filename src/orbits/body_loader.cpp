#include "body_loader.h"

#include <string>
#include <fstream>
#include <locale>
#include <sstream>

#include "star.hpp"
#include "celestialbody.h"

/* Format for files:
 * SUN_NAME,MASS
 * PLANET1_NAME,MASS,ORBITAL_PARAMETERS
 * ...
*/

struct comma_spacing : std::ctype<char> {
	bool is(mask m, char_type c) const {
		if((m & space) && c == ' ') {
			return false;
		}
		if((m & space) && c == ',') {
			return true;
		}
		return ctype::is(m, c);
	}
};

namespace helion {
	SolarSystem::SolarSystem(const std::string &filename) {
		std::ifstream file(filename);
		if(file.is_open()) {
			std::string in_line;
			std::getline(file, in_line);
			std::stringstream line(in_line);
			line.imbue(std::locale(line.getloc(), new comma_spacing()));
			std::string name;
			line >> name;
			double mass;
			line >> mass;
			Star star(mass);
			system[name] = star;
			while(std::getline(file, in_line)) {
				line.str(in_line);
				line >> name;
				line >> mass;
				std::string parent;
				line >> parent;
				double semi, eccen, inclin, lon, aop, top;
				line >> semi;
				line >> eccen;
				line >> inclin;
				line >> lon;
				line >> aop;
				line >> top;
				system[name] = CelestialBody(mass, Orbit(system[parent], semi, eccen, inclin, lon, aop, top));
			}
		}
		file.close();
	}

	void SolarSystem::addBody(std::string name, CelestialBody &body) {
		system.insert({name, body});
	}
}
