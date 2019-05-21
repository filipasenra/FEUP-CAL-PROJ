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

using namespace std;
menu::menu() {
	this->graph = parseMap("T11_nodes_X_Y_Aveiro.txt", "T11_edges_Aveiro.txt", "T11_nodes_lat_lon_Aveiro.txt");
	this->graphPath;
}


void menu::initial() {
	clearScreen();

	cout << endl;  //adicionar opcoes aqui
	cout
			<< "+-----------------------------------------------------------------------+"<< endl;
	cout	<< "|                         Initial Options Menu                          |"<< endl;
	cout	<< "|                                                                       |"<< endl;
	cout	<< "|      1 - Show map                                                     |"<< endl;
	cout	<< "|      2 - Add element to schedule                                      |"<< endl;
	cout	<< "|      3 - Show schedule map                                            |"<< endl;
	cout	<< "|      4 - Exit                                                         |"<< endl;
	cout	<< "|                                                                       |"<< endl;
	cout	<< "+-----------------------------------------------------------------------+"<< endl;

	int opcao;

	cout << "Your option: ";
	cin >> opcao;
	switch (opcao) {
	case 1:
		drawGraph(graph, 1500, 1000);
		getchar();
		break;
	case 2:
		this->addElementSchedule();
		break;
	case 3:
		this->showMapSchedule();
		break;
	case 4:
		this->terminate = true;
		return;
	}

}

void menu::addElementSchedule() {

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

	vector<Vertex<Spot> *> vec = graph.getVertexSet();
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

	Info_calendar info_calendar(spot, hour,  minutes, duration);

	if (schedule.size() == 0){
		this->schedule.push_back(info_calendar);
		return;
	}

	for (size_t i = 0; i < schedule.size(); i++){
		if (info_calendar.getStart() > schedule.at(i).getStart()){
			this->schedule.insert(schedule.begin() + i, info_calendar);
			return;
		}
	}
}


void menu::addingGraph(Graph<Spot> * source, Graph<Spot> * to_be_added) {

	vector<Vertex<Spot> *> vec = to_be_added->getVertexSet();

	for (int i = 0; i < vec.size(); i++) {

		Vertex<Spot> * invertedVertex = vec.at(i);

		source->addVertex(invertedVertex->getInfo());
	}

	for (int i = 0; i < vec.size(); i++) {

		Vertex<Spot> * vertex = vec.at(i);
		vector<Edge<Spot>> edjes = vertex->getEdjes();

		for (int j = 0; j < edjes.size(); j++) {
			source->addEdge(vertex->getInfo(),
					edjes.at(i).getDest()->getInfo(),
					edjes.at(i).getWeight());
			cout << vertex->getInfo().getId() << endl;
		}
	}

}

void menu::makePath(){
	this->graphPath.ResetNodes();
	for (size_t i = 1; i < schedule.size(); i++){
		graph.dijkstraShortestPath(schedule.at(i-1).getSpot(), schedule.at(i).getSpot());
		vector<Spot> path =graph.getPath(schedule.at(i-1).getSpot(), schedule.at(i).getSpot());
		for(size_t k = 0; k < path.size(); k++){
			graphPath.addVertex(path.at(k));
		}
	}
}



void menu::showMapSchedule(){

/*	for(size_t i = 1; i < this->schedule.size(); i++ ){

		graph.dijkstraShortestPath(schedule.at(i-1).getSpot(), schedule.at(i).getSpot());

		graphPath = graph.getPathGraph(schedule.at(i-1).getSpot(), schedule.at(i).getSpot());
	}


*/

	makePath();
	drawGraph(graphPath, 1500, 1000);
	getchar();
}





