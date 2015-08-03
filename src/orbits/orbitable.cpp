#include "orbitable.h"
#include "constants.h"

helion::Orbitable::Orbitable() : mass(0), mu(0), position(glm::vec3(0, 0, 0)) {}

helion::Orbitable::Orbitable(double m) : mass(m), mu(G * m), position(glm::vec3(0, 0, 0)) {}
