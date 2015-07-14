#pragma once

#include <glm/vec3.hpp>

class Orbitable {
public:
	Orbitable();
	Orbitable(double m);
	double mu();
	glm::vec3 position;
	const double mass;
};
