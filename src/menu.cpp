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
		findPath();
		return;
	case 3:
		this->terminate = true;
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

	for (int i = 0; i < vec.size(); i++) {
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

	int start, duration;

	cout << "Start: ";
	while (!(cin >> start)) {
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "Start: ";
	}

	cout << "Duration: ";
	while (!(cin >> duration)) {
		cin.clear();
		cin.ignore(10000, '\n');

		cout << "Duration: ";
	}

	cin.clear();
	cin.ignore(10000, '\n');

	Info_calendar info_calendar(spot, start, duration);

	this->schedule.push_back(info_calendar);

}


void menu::showMapSchedule(){

	for(int i = 1; i < this->schedule.size(); i++ ){

		graph.dijkstraShortestPath(schedule.at(i-1).getSpot(), schedule.at(i).getSpot());
		Graph<Spot> graph2 = graph.getPathGraph(schedule.at(i-1).getSpot(), schedule.at(i).getSpot());
		drawGraph(graph2, 1500, 1000);
	}

}


void menu::findPath(){
	int destino, origem;
	cout << "where are you?(node id)  " << endl;
	cin >> origem;
	cout << "where do you want to go?(node id)   " << endl;
	cin >> destino;
	this->graph.dijkstraShortestPath(Spot(origem), Spot(destino));
	this->graphPath =graph.getPathGraph(origem, destino);
	drawGraph(graphPath, 1500, 1000);
	getchar();
}





