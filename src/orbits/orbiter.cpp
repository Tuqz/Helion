#include "orbiter.h"

#define _USE_MATH_DEFINES
#include <cmath>

void Orbiter::orbit_update(double time) {
	double time_of_flight = time - orbit.time_of_periapsis;
	double tolerance = 5e-13; //Arbitrary value, convergence tolerance
	if(orbit.eccentricity < 1) {
		time_of_flight = time_of_flight - (floor(time_of_flight/orbit.period())*orbit.period());
		double mean_anomaly = (2*M_PI*time_of_flight)/orbit.period();
		double eccen_anomaly = mean_anomaly;
		bool solved = false;
		while(!solved) {
			eccen_anomaly = (orbit.eccentricity*sin(eccen_anomaly) + mean_anomaly - orbit.eccentricity*eccen_anomaly*cos(eccen_anomaly))/(1 - orbit.eccentricity*cos(eccen_anomaly));
			double upper = (eccen_anomaly + tolerance) - orbit.eccentricity*sin(eccen_anomaly + tolerance);
			double lower = (eccen_anomaly - tolerance) - orbit.eccentricity*sin(eccen_anomaly - tolerance);
			if((upper > mean_anomaly) != (lower > mean_anomaly)) { //if the sign changes within the tolerance
				solved = true;
			}
		}
		double tan_true_by_two = sqrt((1 + orbit.eccentricity)/(1 - orbit.eccentricity))*tan(eccen_anomaly/2); //tan(theta/2)
		anomaly = atan(tan_true_by_two)*2;
	} else {
		if(orbit.eccentricity == 1) {
			double mean_anomaly = (M_PI*time_of_flight)/(sqrt(2)*orbit.period());
			double tan_true_by_two = pow((3*mean_anomaly)+sqrt(9*(mean_anomaly*mean_anomaly) + 1), 1.0/3.0) - pow((3*mean_anomaly)+sqrt(9*(mean_anomaly*mean_anomaly) + 1), -1.0/3.0); //Solution to Barker's Equation
			anomaly = 2 * atan(tan_true_by_two);
		} else {
			double mean_anomaly = (2*M_PI*time_of_flight)/orbit.period();
			double eccen_anomaly = mean_anomaly;
			bool solved = false;
			while(!solved) {
				eccen_anomaly = (orbit.eccentricity*eccen_anomaly*cosh(eccen_anomaly)-orbit.eccentricity*sinh(eccen_anomaly) + mean_anomaly)/(orbit.eccentricity*cosh(eccen_anomaly) - 1);
				double upper = -((eccen_anomaly + tolerance) - orbit.eccentricity*sinh(eccen_anomaly + tolerance));
				double lower = -((eccen_anomaly - tolerance) - orbit.eccentricity*sinh(eccen_anomaly - tolerance));
				if((upper > mean_anomaly) != (lower > mean_anomaly)) { //if the sign changes within the tolerance
					solved = true;
				}
			}
			double tan_true_by_two = sqrt((orbit.eccentricity+1)/(orbit.eccentricity-1))*tanh(eccen_anomaly/2);
			anomaly = 2*atan(tan_true_by_two);
		}
	}
}

glm::vec3 Orbiter::position() {
	return orbit.position(anomaly);
}
