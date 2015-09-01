#include "systemloader.h"

#include <string>
#include <fstream>
#include <locale>
#include <sstream>
#include <iostream>
#include <unordered_map>

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

std::shared_ptr<CelestialBody> helion::loadSystem(std::string filename) {
	std::ifstream file(filename);
	std::unordered_map<std::string, std::shared_ptr<CelestialBody>> system; //somewhere to store the objects with identifiers
	std::string sol_name; //name of the sun for retrieval purposes
	if(file.is_open()) {
		std::string in_line;
		std::getline(file, in_line);
		std::stringstream sun_line(in_line);
		sun_line.imbue(std::locale(sun_line.getloc(), new CommaSpacing()));
		sun_line >> sol_name;
		double mass;
		sun_line >> mass;
		system[sol_name] = std::make_shared<Star>(sol_name, mass);
		std::vector<PlanetInfo> postponed; //Any planets that can't be made on first pass - incorrect ordering in file
		while(std::getline(file, in_line)) {
			std::stringstream line(in_line);
			line.imbue(std::locale(line.getloc(), new CommaSpacing()));
			std::string name;
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
					system[name] = std::make_shared<CelestialBody>(name, mass, Orbit(*system[parent], semi, eccen, inclin, lon, aop, top));
					system[parent]->addChild(system[name]);
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
					system[it->name] = std::make_shared<CelestialBody>(it->name, it->mass, Orbit(*system[it->parent], it->semi, it->eccen, it->inclin, it->lon, it->aop, it->top));
					system[it->parent]->addChild(system[it->name]);
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
	return system[sol_name];
}
