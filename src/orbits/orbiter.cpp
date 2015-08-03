#include "orbiter.h"

#include <cmath>
#include <iostream>
#include "constants.h"

using namespace helion;

Orbiter::Orbiter(const Orbit &o) : orbit(o) {
}

void Orbiter::update_orbit(double time) {
	double time_of_flight = time - orbit.getTimeOfPeriapsis(); //time since (first) periapsis
	double tolerance = 5e-13; //Arbitrary value, convergence tolerance
	double period = orbit.getPeriod();
	double e = orbit.getEccentricity();
	if(e < 1) {
		time_of_flight = time_of_flight - floor(time_of_flight/period)*period; //time since latest periapsis
		double mean_anomaly = (2*pi*time_of_flight)/period;
		double eccen_anomaly = mean_anomaly;
		bool solved = false;
		while(!solved) {
			eccen_anomaly = (e*sin(eccen_anomaly) + mean_anomaly - e*eccen_anomaly*cos(eccen_anomaly))/(1 - e*cos(eccen_anomaly)); //Newton-Raphson for Kepler Equation
			double upper = (eccen_anomaly + tolerance) - e*sin(eccen_anomaly + tolerance);
			double lower = (eccen_anomaly - tolerance) - e*sin(eccen_anomaly - tolerance);
			solved = (upper > mean_anomaly) != (lower > mean_anomaly); //if the sign changes, it is solved
		}
		double tan_true_by_two = sqrt((1 + e)/(1 - e))*tan(eccen_anomaly/2); //tan(theta/2)
		anomaly = atan(tan_true_by_two)*2;
	} else {
		if(e == 1) {
			double mean_anomaly = (2*pi*time_of_flight)/period;
			double var = mean_anomaly;
			bool solved = false;
			while(!solved) {
				var = var - ((pow(var, 3) / 3) + var - (mean_anomaly/sqrt(2)))/(pow(var, 2) + 1);
				double upper = (pow(var + tolerance, 3)/3) + var + tolerance;
				double lower = (pow(var - tolerance, 3)/3) + var - tolerance;
				solved = (upper > mean_anomaly/sqrt(2)) != (lower > mean_anomaly/sqrt(2));
			}
			anomaly = atan(var) * 2;
		} else {
			double mean_anomaly = (2*pi*time_of_flight)/period;
			double eccen_anomaly = mean_anomaly;
			bool solved = false;
			while(!solved) {
				eccen_anomaly = (e*eccen_anomaly*cosh(eccen_anomaly)-e*sinh(eccen_anomaly) + mean_anomaly)/(e*cosh(eccen_anomaly) - 1); //Newton-Raphson for Kepler's hyperbolic equation
				double upper = -((eccen_anomaly + tolerance) - e*sinh(eccen_anomaly + tolerance));
				double lower = -((eccen_anomaly - tolerance) - e*sinh(eccen_anomaly - tolerance));
				solved = (upper > mean_anomaly) != (lower > mean_anomaly);
			}
			double tan_true_by_two = sqrt((e+1)/(e-1))*tanh(eccen_anomaly/2);
			anomaly = 2*atan(tan_true_by_two);
		}
	}
	pos = orbit.position(anomaly);
}
