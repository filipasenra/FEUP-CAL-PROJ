/*
 * menu.h
 *
 *  Created on: 20/05/2019
 *      Author: david
 */

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

#include "Graph.h"
#include "Spot.h"
#include "Info_calender.h"



#if __linux__
#define clearScreen() system("clear")
#else
#define clearScreen() system("cls")
#endif


class menu {
private:
	Graph<Spot> graph;
	vector<Info_calender> schedule;

public:
	bool terminate = false;
	menu();
	void initial();
	void addElementSchedule();

};

#endif /* SRC_MENU_H_ */
