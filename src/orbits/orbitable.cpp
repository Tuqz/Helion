#include "orbitable.h"
#include "constants.h"

Orbitable::Orbitable(double m) : mass(m), mu(G * m)
{}
