/*
 * Utilities.cpp
 *
 *  Created on: 26/05/2019
 *      Author: filip
 */

#include "Utilities.h"


double degreesToRadians(double degrees) {
	return degrees * 4 * atan(1) / 180;
}

double distanceCoordinates(Spot spot1, Spot spot2) {

	double earthRadiusKm = 6371;

	double dLat = degreesToRadians(spot1.getLatiLong().getCoordinates_x() - spot2.getLatiLong().getCoordinates_x());
	double dLon = degreesToRadians(spot1.getLatiLong().getCoordinates_y() - spot2.getLatiLong().getCoordinates_y());

	double lat1 = degreesToRadians(spot1.getLatiLong().getCoordinates_x() );
	double lat2 = degreesToRadians(spot2.getLatiLong().getCoordinates_x());

	double a = sin(dLat / 2) * sin(dLat / 2)
			+ sin(dLon / 2) * sin(dLon / 2) * cos(lat1)
					* cos(lat2);

	double c = 2 * atan2(sqrt(a), sqrt(1 - a));

	return earthRadiusKm * c;
}


