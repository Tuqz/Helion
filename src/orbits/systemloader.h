#pragma once

#include <string>
#include <memory>

#include "celestialbody.h"

namespace helion {
	std::shared_ptr<CelestialBody> loadSystem(std::string filename); //returns a pointer to the sun
}
