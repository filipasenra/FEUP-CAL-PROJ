#ifndef _SPOT_
#define _SPOT_

#include <string>
#include "Type.h"

class Coordinates {
private:

	int coordinates_x;
	int coordinates_y;

public:

	Coordinates(int x, int y) :
			coordinates_x(x), coordinates_y(y) {};

	Coordinates() :
				coordinates_x(0), coordinates_y(0) {};

	int getCoordinates_x() {
		return coordinates_x;
	}

	int getCoordinates_y() {
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

	Spot(){};

	Spot(int id, int coordinates_x, int coordinates_y, int lati = 0, int longi =
			0) {
		this->x_y = Coordinates(coordinates_x, coordinates_y);
		this->lat_long = Coordinates(lati, longi);
		this->id = id;
	}

	Spot(int id) {
		this->id = id;

		this->x_y = Coordinates();
		this->lat_long = Coordinates();
	}

	int getId() {
		return id;
	}


	int getCoordinates_x() {
		return this->x_y.getCoordinates_x();
	}

	int getCoordinates_y() {
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

	Coordinates getLatiLong(){
		return lat_long;
	}
};

#endif

