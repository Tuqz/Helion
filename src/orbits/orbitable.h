#pragma once
#include <glm/vec3.hpp>

struct Orbitable {
	Orbitable(double mass);
	glm::vec3 position;
	const double mass, mu;
};
