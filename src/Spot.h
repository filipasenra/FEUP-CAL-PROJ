/**
 * class utilizada para guardar as informaçoes de todos os pontos de um mapa, id, coordenadas
 */

#ifndef _SPOT_
#define _SPOT_

#include <string>
#include "Type.h"

class Coordinates {
private:

	double coordinates_x;
	double coordinates_y;

public:

	Coordinates(double x, double y) :
			coordinates_x(x), coordinates_y(y) {
	}
	;

	Coordinates() :
			coordinates_x(0), coordinates_y(0) {
	}
	;

	double getCoordinates_x() {
		return coordinates_x;
	}

	double getCoordinates_y() {
		return coordinates_y;
	}
};

class Spot {
private:

	int id;

	Coordinates x_y;
	Coordinates lat_long;

public:

	PublicTransp publicTransp;

	Spot() {
	}
	;

	Spot(int id, double coordinates_x, double coordinates_y, double lati = 0,
			double longi = 0) {
		this->x_y = Coordinates(coordinates_x, coordinates_y);
		this->lat_long = Coordinates(lati, longi);
		this->id = id;
	}

	Spot(int id) {
		this->id = id;

		this->x_y = Coordinates();
		this->lat_long = Coordinates();
	}

	int getId() const {
		return id;
	}

	double getCoordinates_x() {
		return this->x_y.getCoordinates_x();
	}

	double getCoordinates_y() {
		return this->x_y.getCoordinates_y();
	}

	bool operator ==(Spot spot) {
		return (id == spot.getId());
	}

	bool hasBusStop() {
		return (publicTransp.bus.size() != 0);
	}

	bool hasSubwayStop() {
		return (publicTransp.subway.size() != 0);
	}

	Coordinates getLatiLong() {
		return lat_long;
	}

	bool hasSameBusStation(Spot spot) {

		for (unsigned int i = 0; i < spot.publicTransp.bus.size(); i++) {

			for (unsigned int j = 0; j < this->publicTransp.bus.size(); j++) {
				if (spot.publicTransp.bus.at(i).line
						== this->publicTransp.bus.at(j).line) {
					return true;
				}
			}
		}

		return false;
	}

	bool hasSameSubWayStation(Spot spot) {

		for (unsigned int i = 0; i < spot.publicTransp.subway.size(); i++) {

			for (unsigned int j = 0; j < this->publicTransp.subway.size(); j++) {
				if (spot.publicTransp.subway.at(i).line
						== this->publicTransp.subway.at(j).line) {
					return true;
				}
			}
		}

		return false;
	}
};

#endif

