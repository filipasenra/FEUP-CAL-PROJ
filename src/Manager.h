#ifndef _MANAGER_
#define _MANAGER_

#include "Calender.h"
#include "Graph.h"

class Manager{
private:
	Calender calender;
	Graph<Spot> network;
	Graph<Info_calender> journey;

public:
	Manager(){
	};

};

#endif
