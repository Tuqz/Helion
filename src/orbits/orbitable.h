#pragma once
#include <glm/vec3.hpp>

namespace helion {
	struct Orbitable {
		Orbitable();
		Orbitable(double mass);
		const double mass, mu;
		glm::vec3 position;
	};
}
