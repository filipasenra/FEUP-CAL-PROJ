#ifndef _TYPE_
#define _TYPE_

class TranspStop {
public:
	int id_nearby;
	string codStop;
	string line;

public:
	TranspStop(int id_nearby, string codStop, string line) {

		this->id_nearby = id_nearby;
		this->codStop = codStop;
		this->line = line;
	}
};

enum TypeBusStop {
	SHELTER, POLE, MARKING
};

class Bus: public TranspStop {

	string codZone;
	string county;
	string parish;
	string adress;
	TypeBusStop typeStop = MARKING;

public:
	Bus(int id_nearby, string codStop, string line) :
			TranspStop(id_nearby, codStop, line) {
	}
	;
};

class Subway: public TranspStop {
public:
	Subway(int id_nearby, string codStop, string line) :
			TranspStop(id_nearby, codStop, line) {
	}
	;
};

class PublicTransp {

public:
	vector<Bus> bus;
	vector<Subway> subway;
};

#endif
