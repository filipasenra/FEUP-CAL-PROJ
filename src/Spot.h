#ifndef _SPOT_
#define _SPOT_


class Spot{
private:
	int coordinates_y;
	int coordinates_x;
	string name;

public:
	Spot(int coordinates_y, int coordinates_x, string name){
		this->coordinates_x=coordinates_x;
		this->coordinates_y = coordinates_y;
		this->name = name;
	}

	int getCoordinates_x(){
		return coordinates_x;
	}

	int getCoordinates_y(){
		return coordinates_y;
	}

	string getName(){
		return name;
	}
};

#endif

