#include "orbitable.h"
#include "constants.h"

using namespace helion; 

Orbitable::Orbitable(double m) : mass(m), mu(G * m)
{}
