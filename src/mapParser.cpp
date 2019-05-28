#include "mapParser.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include "Spot.h"
#include <math.h>
#include <map>
#include <iostream>
#include <set>
#include <algorithm>
#include "Utilities.h"

void parseX_YFile(Graph * graph, std::string X_YFile,
		std::string Lat_LongFile) {

	ifstream file_X_Y;
	file_X_Y.open(X_YFile);

	ifstream file_Lat_Long;
	file_Lat_Long.open(Lat_LongFile);

	if (!file_X_Y.is_open()) {
		cout << "Error opening " << X_YFile << ".\n";
		exit(1);
	}

	if (!file_Lat_Long.is_open()) {
		cout << "Error opening " << Lat_LongFile << ".\n";
		exit(2);
	}

	string line, line2;
	int number_of_nodes = 0, number_of_nodes2 = 0;

	std::getline(file_X_Y, line);
	std::istringstream iss(line);
	iss >> number_of_nodes;

	getline(file_Lat_Long, line2);
	std::istringstream iss2(line2);
	iss2 >> number_of_nodes2;

	if (number_of_nodes2 != number_of_nodes) {
		cout << "Files are incompatible!\n";
		exit(3);
	}

	while (std::getline(file_X_Y, line) && number_of_nodes != 0
			&& std::getline(file_Lat_Long, line2) && number_of_nodes != 0) {
		number_of_nodes--;
		number_of_nodes2--;

		int id;
		double coordinates_x;
		double coordinates_y;

		int id2;
		double latitude;
		double longitude;

		sscanf(line.c_str(), "(%d, %lf, %lf)", &id, &coordinates_x,
				&coordinates_y);

		sscanf(line2.c_str(), "(%d, %lf, %lf)", &id2, &latitude, &longitude);

		if (id2 != id) {
			cout << "Error in nodes of files!\n";
			exit(4);
		}

		Spot spot(id, coordinates_x, coordinates_y, latitude, longitude);

		graph->addVertex(spot);

	}

}

void parseEdgesFile(Graph * graph, std::string edgesFile,
		TYPE_TRANSPORTATION tp = FOOT) {

	ifstream file_edges;
	file_edges.open(edgesFile);

	if (!file_edges.is_open()) {
		cout << "Error opening " << edgesFile << ".\n";
		exit(2);
	}

	string line;
	int number_of_nodes = 0;

	std::getline(file_edges, line);
	std::istringstream iss(line);
	iss >> number_of_nodes;

	vector<Vertex *> vec = graph->getVertexSet();

	while (std::getline(file_edges, line) && number_of_nodes != 0) {
		number_of_nodes--;

		int id1 = 0, id2 = 0;

		sscanf(line.c_str(), "(%d, %d)", &id1, &id2);

		double weight;

		Vertex * a = graph->findVertex(Spot(id1));
		Vertex * b = graph->findVertex(Spot(id2));

		if (a == NULL || b == NULL)
			continue;

		weight = distanceCoordinates(a->getInfo(), b->getInfo());

		a->addEdge(b, weight, tp);
		b->addEdge(a, weight, tp);

	}

}

void makeLinesBus(Graph * graph, set<string> bus) {

	vector<Vertex *> vec = graph->getVertexSet();

	for (set<string>::const_iterator it = bus.begin(); it != bus.end(); it++) {

		Graph graph_line;

		string line = *it;

		for (unsigned int i = 0; i < vec.size(); i++) {

			vector<Bus> bus = vec.at(i)->getInfo().publicTransp.bus;

			for (unsigned int k = 0; k < bus.size(); k++) {
				if (bus.at(k).line == line) {
					graph_line.addVertex(vec.at(i)->getInfo());
					break;
				}
			}
		}


		graph_line.connectingStations();

		vector<Vertex *> vec2 = graph_line.getVertexSet();

		for(unsigned int k = 0; k < vec2.size(); k++){

			Vertex * vertex1 = graph->findVertex(vec2.at(k)->getInfo());

			if(vec2.at(k)->path != nullptr){
				Vertex * vertex2 = graph->findVertex(vec2.at(k)->path->getInfo());

				double weight = distanceCoordinates(vertex1->getInfo(), vertex2->getInfo());

				vertex1->addEdge(vertex2, weight, BUS);
				vertex2->addEdge(vertex1, weight, BUS);
			}
		}
	}
}

void parseBusFile(Graph * graph, std::string busFile) {

	ifstream file_bus;
	file_bus.open(busFile);

	if (!file_bus.is_open()) {
		cout << "Error opening " << busFile << ".\n";
		exit(2);
	}

	string line;
	int number_of_nodes = 0;

	std::getline(file_bus, line);
	std::istringstream iss(line);
	iss >> number_of_nodes;

	set<string> bus_lines;
	char random[50];

	while (std::getline(file_bus, line) && number_of_nodes != 0) {
		number_of_nodes--;

		int id;
		char codStop[10], codLine[10];

		//%s eats the comma %[^,\n] does not
		sscanf(line.c_str(),
				"(%d, %[^,\n], %[^,\n], %[^,\n], %[^,\n], %[^,\n], %[^,\n], %[^)\n])",
				&id, codStop, codLine, random, random, random, random, random);

		Vertex * vertex = graph->findVertex(Spot(id));

		if (vertex == NULL)
			continue;

		Bus bus(id, string(codStop), string(codLine));
		vertex->getPointerInfo()->publicTransp.bus.push_back(bus);
		bus_lines.insert(bus.line);

	}

	makeLinesBus(graph, bus_lines);

}

void makeLinesSubway(Graph * graph, set<string> subwayLines) {

	vector<Vertex *> vec = graph->getVertexSet();

	for (set<string>::const_iterator it = subwayLines.begin(); it != subwayLines.end(); it++) {

		Graph graph_line;

		string line = *it;

		for (unsigned int i = 0; i < vec.size(); i++) {

			vector<Subway> subway = vec.at(i)->getInfo().publicTransp.subway;

			for (unsigned int k = 0; k < subway.size(); k++) {
				if (subway.at(k).line == line) {
					graph_line.addVertex(vec.at(i)->getInfo());
					break;
				}
			}
		}


		graph_line.connectingStations();

		vector<Vertex *> vec2 = graph_line.getVertexSet();

		for(unsigned int k = 0; k < vec2.size(); k++){

			Vertex * vertex1 = graph->findVertex(vec2.at(k)->getInfo());

			if(vec2.at(k)->path != nullptr){
				Vertex * vertex2 = graph->findVertex(vec2.at(k)->path->getInfo());

				double weight = distanceCoordinates(vertex1->getInfo(), vertex2->getInfo());

				vertex1->addEdge(vertex2, weight, SUBWAY);
				vertex2->addEdge(vertex1, weight, SUBWAY);
			}
		}
	}
}

void parseSubwayFile(Graph * graph, std::string subwayFile) {
	ifstream file_subway;
	file_subway.open(subwayFile);

	if (!file_subway.is_open()) {
		cout << "Error opening " << subwayFile << ".\n";
		exit(2);
	}

	string line;
	int number_of_nodes = 0;

	std::getline(file_subway, line);
	std::istringstream iss(line);
	iss >> number_of_nodes;

	set<string> subwayLines;

	while (std::getline(file_subway, line) && number_of_nodes != 0) {
		number_of_nodes--;

		int id;
		char nome1[250], linhas1[250];
		string linha;

		sscanf(line.c_str(), "(%d, '%[^'\n]', %[^)\n])", &id, nome1, linhas1);

		string nome(nome1);
		string linhas(linhas1);

		for (size_t i = 0; i < linhas.size(); i++) {

			if (linhas[2] == ')') {
				break;
			} else {

				linha = linhas[2];
				linhas = linhas.substr(5, linhas.size());
				Vertex * vertex = graph->findVertex(Spot(id));

				if (vertex == NULL)
					continue;
				Subway subway(id, nome, linha);

				vertex->getPointerInfo()->publicTransp.subway.push_back(subway);
				subwayLines.insert(subway.line);
			}
		}

	}

	makeLinesSubway(graph, subwayLines);

}

Graph parseMap(std::string X_YFile, std::string edgesFile,
		std::string Lat_LongFile, std::string busFile,
		std::string subawayFile) {

	Graph graph;

	parseX_YFile(&graph, X_YFile, Lat_LongFile);

	parseEdgesFile(&graph, edgesFile);

	if (busFile != "")
		parseBusFile(&graph, busFile);

	if (subawayFile != "")
		parseSubwayFile(&graph, subawayFile);

	return graph;

}
