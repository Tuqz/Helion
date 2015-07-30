#pragma once
#include <glm/vec3.hpp>

namespace helion {
	class Orbitable {
	public:
		Orbitable();
		Orbitable(double mass);
		glm::vec3 position;
		double getMass();
		double getMu();
	private:
		double mass, mu;
	};
}
