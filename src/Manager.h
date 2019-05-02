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
	//Name is the name of the file that contains
	//the information about the netWork
	Manager(string name){
		//this->loadNetwork(name)
	};

	int loadNetWork(string name);

	int addSpot();

	Graph<Info_calender> getJourney()
	{
		return journey;
	};

	Graph<Spot> getNetWork(){
		return network;
	}

};

#endif
