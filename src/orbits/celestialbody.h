#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include <glm/vec3.hpp>

#include "orbit.h"
#include "orbiter.h"
#include "celestialfunction.h"

namespace helion {
	class Orbit;
	class CelestialBody : public Orbiter {
	public:
		std::string name;

		CelestialBody();
		CelestialBody(std::string name, double mass, const Orbit &orbit);
		virtual ~CelestialBody();

		double mu() const;
		virtual glm::vec3 getPosition() const;

		virtual void update(double time);
		void addChild(std::shared_ptr<CelestialBody> child);
		void apply(CelestialFunction &func); //apply the function to all of the tree below here
	private:
		double mass;
		std::vector<std::shared_ptr<CelestialBody>> children;
	};
}
