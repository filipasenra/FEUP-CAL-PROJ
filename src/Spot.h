#ifndef _SPOT_
#define _SPOT_

#include <string>
#include "Type.h"

class Spot {
private:
	int coordinates_y;
	int coordinates_x;
	int id;
	Type type;

public:
	Spot(int coordinates_y, int coordinates_x, int id) {
		this->coordinates_x = coordinates_x;
		this->coordinates_y = coordinates_y;
		this->id = id;
		this->type = Type::FOOT;
	}

	Spot(int id) {
		this->id = id;
		this->coordinates_x = 0;
		this->coordinates_y = 0;
		this->id = id;
		this->type = Type::FOOT;
	}

	void setType(Type type) {
		this->type = type;
	}

	int getCoordinates_x() {
		return coordinates_x;
	}

	int getCoordinates_y() {
		return coordinates_y;
	}

	int getId() {
		return id;
	}

	int getType() {
		return type;
	}

	bool operator ==(Spot spot) {
		return (id == spot.getId());
	}
};

#endif

