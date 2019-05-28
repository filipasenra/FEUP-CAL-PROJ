/*
 * class usada para guardar as informações de uma estação: bus ou subway
 */

#ifndef _TYPE_
#define _TYPE_

#include <string>
#include <vector>
#include <iostream>

class TranspStop {
public:
	int id_nearby;
	std::string codStop;
	std::string line;

public:
	TranspStop(int id_nearby, std::string codStop, std::string line) {

		this->id_nearby = id_nearby;
		this->codStop = codStop;
		this->line = line;
	}
};

enum TypeBusStop {
	SHELTER, POLE, MARKING
};

class Bus: public TranspStop {

	std::string codZone;
	std::string county;
	std::string parish;
	std::string adress;
	TypeBusStop typeStop = MARKING;

public:
	Bus(int id_nearby, std::string codStop, std::string line) :
			TranspStop(id_nearby, codStop, line) {
	}
	;
};

class Subway: public TranspStop {
public:
	Subway(int id_nearby, std::string codStop, std::string line) :
			TranspStop(id_nearby, codStop, line) {
	}
	;
};

class PublicTransp {

public:
	std::vector<Bus> bus;
	std::vector<Subway> subway;
};

#endif
