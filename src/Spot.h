#ifndef _SPOT_
#define _SPOT_

#include <string>
#include "Type.h"

class Spot{
private:
	int coordinates_y;
	int coordinates_x;
	int id;
	Type type;

public:
	Spot(int coordinates_y, int coordinates_x, int id, Type type){
		this->coordinates_x=coordinates_x;
		this->coordinates_y = coordinates_y;
		this->id = id;
		this->type = type;
	}

	int getCoordinates_x(){
		return coordinates_x;
	}

	int getCoordinates_y(){
		return coordinates_y;
	}

	int getId(){
		return id;
	}

	int getType(){
		return type;
	}

	bool operator ==(Spot spot){
		return (coordinates_y == spot.getCoordinates_y() && coordinates_x == spot.getCoordinates_x());
	}
};

#endif

