#include "mapParser.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include "Spot.h"

void parseX_YFile(Graph<Spot> * graph, std::string X_YFile) {

	ifstream file_X_Y;
	file_X_Y.open(X_YFile);

	if (!file_X_Y.is_open()) {
		cout << "Error opening " << X_YFile << ".\n";
		exit(1);
	}

	string line;
	int number_of_nodes = 0;

	std::getline(file_X_Y, line);
	std::istringstream iss(line);
	iss >> number_of_nodes;

	while (std::getline(file_X_Y, line) && number_of_nodes != 0) {
		number_of_nodes--;

		int id;
		double coordinates_x;
		double coordinates_y;

		sscanf(line.c_str(), "(%d, %lf, %lf)", &id, &coordinates_x,
				&coordinates_y);

		Spot spot(id, coordinates_x, coordinates_y);
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

	while (std::getline(file_edges, line) && number_of_nodes != 0) {
		number_of_nodes--;

		int id1, id2;

		sscanf(line.c_str(), "(%d, %d)", &id1, &id2);

		graph->addEdge(Spot(id1), Spot(id2), 1);

	}

}

Graph<Spot> parseMap(std::string X_YFile, std::string edgesFile/*,
 std::string tagsFile*/) {

	Graph<Spot> graph;

	parseX_YFile(&graph, X_YFile);



	return graph;

}
