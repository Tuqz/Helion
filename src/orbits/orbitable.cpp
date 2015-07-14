#include "orbitable.h"

Orbitable::Orbitable() : mass(0) {
}

Orbitable::Orbitable(double m) : mass(m) {
}

double Orbitable::mu() {
	return (6.67e-11)*mass; //get new G and isolate it
}
