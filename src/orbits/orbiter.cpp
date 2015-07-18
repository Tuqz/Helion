#include "orbiter.h"

#include <cmath>
#include "constants.h"

void Orbiter::update_orbit(double time) {
	double time_of_flight = time - orbit.time_of_periapsis; //time since (first) periapsis
	double tolerance = 5e-13; //Arbitrary value, convergence tolerance
	if(orbit.eccentricity < 1) {
		time_of_flight = time_of_flight - floor(time_of_flight/orbit.period)*orbit.period; //time since latest periapsis
		double mean_anomaly = (2*pi*time_of_flight)/orbit.period;
		double eccen_anomaly = mean_anomaly;
		bool solved = false;
		while(!solved) {
			eccen_anomaly = (orbit.eccentricity*sin(eccen_anomaly) + mean_anomaly - orbit.eccentricity*eccen_anomaly*cos(eccen_anomaly))/(1 - orbit.eccentricity*cos(eccen_anomaly)); //Newton-Raphson for Kepler Equation
			double upper = (eccen_anomaly + tolerance) - orbit.eccentricity*sin(eccen_anomaly + tolerance);
			double lower = (eccen_anomaly - tolerance) - orbit.eccentricity*sin(eccen_anomaly - tolerance);
			solved = (upper > mean_anomaly) != (lower > mean_anomaly); //if the sign changes, it is solved
		}
		double tan_true_by_two = sqrt((1 + orbit.eccentricity)/(1 - orbit.eccentricity))*tan(eccen_anomaly/2); //tan(theta/2)
		anomaly = atan(tan_true_by_two)*2;
	} else { //if we encounter issues we need to support e exactly equals 1 (unlikely due to floats)
		double mean_anomaly = (2*pi*time_of_flight)/orbit.period();
		double eccen_anomaly = mean_anomaly, upper, lower;
		bool solved = false;
		while(!solved) {
			eccen_anomaly = (orbit.eccentricity*eccen_anomaly*cosh(eccen_anomaly)-orbit.eccentricity*sinh(eccen_anomaly) + mean_anomaly)/(orbit.eccentricity*cosh(eccen_anomaly) - 1); //Newton-Raphson for Kepler's hyperbolic equation
			upper = -((eccen_anomaly + tolerance) - orbit.eccentricity*sinh(eccen_anomaly + tolerance));
			lower = -((eccen_anomaly - tolerance) - orbit.eccentricity*sinh(eccen_anomaly - tolerance));
		}
		double tan_true_by_two = sqrt((orbit.eccentricity+1)/(orbit.eccentricity-1))*tanh(eccen_anomaly/2);
		anomaly = 2*atan(tan_true_by_two);
	}
	position = orbit.position(anomaly);
}
