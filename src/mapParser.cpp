#include "mapParser.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include "Spot.h"
#include <math.h>

void parseX_YFile(Graph<Spot> * graph, std::string X_YFile,
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

void parseEdgesFile(Graph<Spot> * graph, std::string edgesFile) {

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

	int n_edge = 0;

	while (std::getline(file_edges, line) && number_of_nodes != 0) {
		number_of_nodes--;

		int id1 = 0, id2 = 0;

		sscanf(line.c_str(), "(%d, %d)", &id1, &id2);

		double weight;
		Spot spot = Spot(id1);
		Spot spot2 = Spot(id2);
		Vertex<Spot> * a = graph->findVertex(spot);
		Vertex<Spot> * b = graph->findVertex(spot2);

		if (a == NULL || b == NULL)
			continue;

		weight = sqrt(
				pow(
						a->getInfo().getCoordinates_x()
								- b->getInfo().getCoordinates_x(), 2)
						+ pow(
								a->getInfo().getCoordinates_y()
										- b->getInfo().getCoordinates_y(), 2));

		graph->addEdge(Spot(id1), Spot(id2), weight);

	}

}

void parseBusFile(Graph<Spot> * graph, std::string busFile) {

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

	while (std::getline(file_bus, line) && number_of_nodes != 0) {
		number_of_nodes--;

		int id;
		char codStop[10], codLine[10];

		//%s eats the comma %[^,\n] does not
		sscanf(line.c_str(), "(%d, %[^,\n], %[^,\n], %[^,\n], %[^,\n], %[^,\n], %[^,\n], %[^,\n])", &id, codStop, codLine, NULL, NULL, NULL, NULL, NULL);

		Vertex<Spot> * vertex = graph->findVertex(Spot(id));

		if(vertex == NULL)
			continue;

		Bus bus(id, string (codStop), string (codLine));
		vertex->getPointerInfo()->publicTransp.bus.push_back(bus);

	}

}

Graph<Spot> parseMap(std::string X_YFile, std::string edgesFile,
		std::string Lat_LongFile, std::string busFile /*,
		 std::string tagsFile*/) {

	Graph<Spot> graph;

	parseX_YFile(&graph, X_YFile, Lat_LongFile);

	parseEdgesFile(&graph, edgesFile);

	if(busFile != "")
		parseBusFile(&graph, busFile);

	return graph;

}
