#pragma once

#include "celestialbody.h"

namespace helion {
	class CelestialFunction {
	public:
		virtual void call(CelestialBody *body) = 0;
	};
}
