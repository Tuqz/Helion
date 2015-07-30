#include "bodyloader.h"
#include <fstream>
#include <sstream>

namespace helion {
	Orbitable loadSun(std::string filename) {
		std::ifstream datafile(filename);
		if(datafile.is_open()) {
			std::string data;
			std::getline(datafile, data);
			datafile.close();
			return Orbitable(std::stod(data, nullptr)); //file should only contain the mass of the object
		} else {
			return Orbitable(-1); //return a repulsive body, easy to test for
		}
	}

	SolarSystem loadSystem(Orbitable *sun, std::string filename) {
		std::ifstream datafile(filename);
		SolarSystem system;
		if(datafile.is_open()) {
			std::string data;
			while(getline(datafile, data)) {
				//File structure is NAME,MASS,PARENT,A,E,I,OMEGA,ARG,T
				std::stringstream line(data);
				std::string name;
				getline(line, name, ',');
				std::string m;
				getline(line, m, ',');
				double mass = std::stod(m);
				std::string parent;
				getline(line, parent, ',');
				std::string s;
				getline(line, s, ',');
				double semimajor = std::stod(s);
				std::string e;
				getline(line, e, ',');
				double eccen = std::stod(e);
				std::string i;
				getline(line, i, ',');
				double inclin = std::stod(i);
				std::string l;
				getline(line, l, ',');
				double longitude = std::stod(l);
				std::string a;
				getline(line, a, ',');
				double argument = std::stod(a);
				std::string t;
				getline(line, t, ',');
				double time = std::stod(t);
				if(parent == "Sun") { //If it is a planet
					Orbit orbit(sun, semimajor, eccen, inclin, longitude, argument, time);
					CelestialBody body(mass, orbit);
					system.insert({{name, body}});
				} else {
					Orbit orbit(&system.at(parent), semimajor, eccen, inclin, longitude, argument, time);
					CelestialBody body(mass, orbit);
					system.insert({{name, body}});
				}
			}
		}
		return system;
	}
}
