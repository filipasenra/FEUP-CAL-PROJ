/*
 * menu.cpp
 *
 *  Created on: 20/05/2019
 *      Author: david
 */

#include "menu.h"
#include <iostream>
#include "mapParser.h"
#include "Draw.h"
#include "Graph.h"
#include "BiDirectionalDijkstra.h"
#include <vector>

using namespace std;
menu::menu() {

	cout << "Loading Map..." << endl;

	this->graph = parseMap("T11_nodes_X_Y_Porto.txt", "T11_edges_Porto.txt",
			"T11_nodes_lat_lon_Porto.txt", "stcp_routes_Porto.txt", "metro_routes_Porto.txt");

	schedule.push_back(Info_calendar(graph.findVertex(Spot(280200623))->getInfo(), 10, 10, 10));
	schedule.push_back(Info_calendar(graph.findVertex(Spot(90379359))->getInfo(), 11, 10, 10));
	schedule.push_back(Info_calendar(graph.findVertex(Spot(343646668))->getInfo(), 12, 10, 10));
}





void menu::initial() {
	clearScreen();

	cout << endl;  //adicionar opcoes aqui
	cout
			<< "+-----------------------------------------------------------------------+"
			<< endl;
	cout
			<< "|                         Initial Options Menu                          |"
			<< endl;
	cout
			<< "|                                                                       |"
			<< endl;
	cout
			<< "|      1 - Show map                                                     |"
			<< endl;
	cout
			<< "|      2 - Add element to schedule                                      |"
			<< endl;
	cout
			<< "|      3 - Remove element in schedule                                   |"
			<< endl;
	cout
			<< "|      4 - Show schedule map                                            |"
			<< endl;
	cout
			<< "|      5 - Exit                                                         |"
			<< endl;
	cout
			<< "|                                                                       |"
			<< endl;
	cout
			<< "+-----------------------------------------------------------------------+"
			<< endl;

	int opcao;

	cout << "Your option: ";
	cin >> opcao;
	switch (opcao) {
	case 1:
		drawGraph(graph, 1500, 1000);
		getchar();
		break;
	case 2:
		this->addElementScedule();
		break;
	case 3:
		this->removeElementSchedule();
		break;
	case 4:
		this->showMapSchedule();
		break;
	case 5:
		this->terminate = true;
		break;
	}
	return;

}

void menu::addElementScedule() {

	cin.clear();
	cin.ignore(10000, '\n');

	for (size_t i = 0; i < schedule.size(); i++) {
		cout << i + 1 << "- " << schedule.at(i).getSpot().getId() <<
				" at time:" << schedule.at(i).getStart()/60 << ":" <<
				schedule.at(i).getStart()%60 << " with duration:" <<
				schedule.at(i).getDuration() << " minutes" << endl;
	}
	double coordinates_x, coordinates_y;

	cout << "Longitude: ";
	while (!(cin >> coordinates_x)) {
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "Longitude: ";
	}

	cout << "Latitude: ";
	while (!(cin >> coordinates_y)) {
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "Latitude: ";
	}

	vector<Vertex *> vec = graph.getVertexSet();
	Spot spot;
	bool passed;

	for (size_t i = 0; i < vec.size(); i++) {
		Coordinates latlong = vec.at(i)->getInfo().getLatiLong();

		if ((latlong.getCoordinates_x()) == coordinates_x
				&& (latlong.getCoordinates_y()) == coordinates_y) {
			spot = vec.at(i)->getInfo();
			passed = true;
			break;
		}
	}

	if (!passed) {
		cout << "Spot was not found!\n";
		return;
	}

	int hour, minutes, duration;

	cout << "hour: ";
	while (!(cin >> hour)) {
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "hour: ";
	}

	cout << "minutes: ";
	while (!(cin >> minutes)) {
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "minutes: ";
	}

	cout << "Duration: ";
	while (!(cin >> duration)) {
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "Duration: ";
	}

	cin.clear();
	cin.ignore(10000, '\n');

	Info_calendar info_calendar(spot, hour, minutes, duration);

	for (size_t i = 0; i < schedule.size(); i++) {
		if (schedule.at(i).sameTime(info_calendar)){
			cout << "Can't add activity because there are other at the same time! \n";
			return;
		}
	}

	this->schedule.push_back(info_calendar);

	sort(schedule.begin(), schedule.end());
}


void menu::removeElementSchedule(){

	cin.clear();
	cin.ignore(10000, '\n');

	for (size_t i = 0; i < schedule.size(); i++) {
		cout << i + 1 << "- " << schedule.at(i).getSpot().getId() <<
				" at time:" << schedule.at(i).getStart()/60 << ":" <<
				schedule.at(i).getStart()%60 << " with duration:" <<
				schedule.at(i).getDuration() << " minutes" << endl;
	}

	cout << "which one do you want to remove? (number, 0 to cancel)" << endl;
	int option;
	cin >> option;
	if (option == 0){
		return;
	}
	else{
		schedule.erase(schedule.begin() + option-1);
	}

}

void menu::showMapSchedule() {

	double weight = 0;
	graph.resetPath();
	Graph graph2;
	for (size_t i = 1; i < this->schedule.size(); i++) {

		if (!graph.isPathPossible(schedule.at(i - 1).getSpot(), schedule.at(i).getSpot())) {
			cout << "Path is not possible between " << schedule.at(i - 1).getSpot().getId() << " and " << schedule.at(i).getSpot().getId() << "!\n";
			continue;
		}

		BiDirectionalDijsktra bid(graph);

		bid.bidirectionaldijsktrafastest(schedule.at(i - 1).getSpot(),
				schedule.at(i).getSpot());

		weight += bid.getTotalWeight();

		bid.getPathGraphBi();

		/*graph.dijkstraFastestPath(schedule.at(i - 1).getSpot(),
				schedule.at(i).getSpot());

		weight += graph.findVertex(schedule.at(i).getSpot())->dist;

		graph.getPathGraph(schedule.at(i - 1).getSpot(),
				schedule.at(i).getSpot());*/
	}

	if (weight < INF) {
		drawPath(graph, 1500, 1000);
		cout << "The total weight of the trip is: " << weight * 60 << "." << endl;
		getchar();
	} else
		cout << "No path found!\n";
}

