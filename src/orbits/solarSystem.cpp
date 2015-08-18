#include "solarSystem.h"

#include <string>
#include <fstream>
#include <locale>
#include <sstream>

#include <iostream>

#include "star.hpp"
#include "celestialbody.h"

/* Format for files:
 * SUN_NAME,MASS
 * PLANET1_NAME,MASS,ORBITAL_PARAMETERS
 * ...
*/

using namespace helion;

struct CommaSpacing : std::ctype<char> {
	CommaSpacing() : std::ctype<char>(get_table()) {}
	static mask *get_table() {
		static mask rc[table_size];
		rc[','] = std::ctype_base::space;
		rc['\n'] = std::ctype_base::space;
		return &rc[0];
	}
};

struct PlanetInfo {
	PlanetInfo(std::string n, std::string p, double m, double s, double e, double i, double l, double a, double t) {
		name = n;
		parent = p;
		mass = m;
		semi = s;
		eccen = e;
		inclin = i;
		lon = l;
		aop = a;
		top = t;
	}

	std::string name, parent;
	double mass, semi, eccen, inclin, lon, aop, top;
};

SolarSystem::SolarSystem(const std::string &filename) {
	std::ifstream file(filename);
	if(file.is_open()) {
		std::string in_line;
		std::getline(file, in_line);
		std::stringstream sun_line(in_line);
		sun_line.imbue(std::locale(sun_line.getloc(), new CommaSpacing()));
		std::string name;
		sun_line >> name;
		double mass;
		sun_line >> mass;
		addBody(name, Star(mass));
		std::vector<PlanetInfo> postponed; //Any planets that can't be made on first pass - incorrect ordering in file
		while(std::getline(file, in_line)) {
			std::stringstream line(in_line);
			line.imbue(std::locale(line.getloc(), new CommaSpacing()));
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
			if(system.find(name) == system.end()) { //body not already present
				if(system.find(parent) != system.end()) { //parent present
					addBody(name, CelestialBody(mass, Orbit(system[parent], semi, eccen, inclin, lon, aop, top)));
				} else {
					PlanetInfo info(name, parent, mass, semi, eccen, inclin, lon, aop, top);
					postponed.push_back(info);
				}
			} else {
				std::cout << "Duplicate entry of " << name << std::endl;
			}
		}

		bool stopped = false;
		while(!stopped) {
			stopped = true;
			for(auto it = postponed.begin(); it != postponed.end(); ++it) {
				if(system.find(it->parent) != system.end()) {
					stopped = false;
					addBody(it->name, CelestialBody(it->mass, Orbit(system[it->parent], it->semi, it->eccen, it->inclin, it->lon, it->aop, it->top)));
					postponed.erase(it);
					--it;
				}
			}
		}
		for(auto it : postponed) {
			std::cout << "Failed to load " << it.name << std::endl;
		}
	}
	file.close();
}

void SolarSystem::addBody(std::string name, CelestialBody &body) {
	system.insert({name, body});
}

void SolarSystem::addBody(std::string name, CelestialBody &&body) {
	system.insert({name, body});
}

CelestialBody &SolarSystem::getBody(std::string name) {
	return system[name];
}
