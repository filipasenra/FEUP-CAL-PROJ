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
	this->graph = parseMap("T11_nodes_X_Y_Porto.txt", "T11_edges_Porto.txt",
			"T11_nodes_lat_lon_Porto.txt");

}



int getPathWeight(){

}

void nearestneighbour(Spot origin, Spot dest, Graph graph){
	vector<Spot> bus;
	for (size_t i = 0; i < graph.getVertexSet().size(); i++){
		if (graph.getVertexSet().at(i)->getInfo().hasBusStop()){
			bus.push_back(graph.getVertexSet().at(i)->getInfo());
		}

	}
	return;
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
			<< "|      3 - Show schedule map                                            |"
			<< endl;
	cout
			<< "|      4 - Exit                                                         |"
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
		this->showMapSchedule();
		break;
	case 4:
		this->terminate = true;
		return;
	}

}

void menu::addElementScedule() {

	cin.clear();
	cin.ignore(10000, '\n');

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

	this->schedule.push_back(info_calendar);

	sort(schedule.begin(), schedule.end());
}

void menu::showMapSchedule() {

	Graph graphPath;

	for (size_t i = 1; i < this->schedule.size(); i++) {
		Graph new_graph;

		if (graph.findVertex(schedule.at(i).getSpot())->visited) {
			i++;
			cout << "Spot is disconected!\n";
			continue;
		}

		graph.dijkstraShortestPath(schedule.at(i - 1).getSpot(),
				schedule.at(i).getSpot());

		new_graph = graph.getPathGraph(schedule.at(i - 1).getSpot(),
				schedule.at(i).getSpot());

		addingGraph(&graphPath, &new_graph);
	}

	if (graphPath.getNumVertex() != 0) {
		drawGraph(graphPath, 1500, 1000);
		getchar();
	} else
		cout << "No path found!\n";
}

