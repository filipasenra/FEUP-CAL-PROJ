#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "BiDirectionalDijkstra.h"
#include "mapParser.h"
#include "draw.h"
#include "menu.h"
#include <math.h>

int main() {

	Graph graph = parseMap("T11_nodes_X_Y_Aveiro.txt", "T11_edges_Aveiro.txt",
			"T11_nodes_lat_lon_Aveiro.txt");

	//before drawing we have to normalize the coordinates
	//drawGraph(graph, 1500, 1000);

	//graph.dijkstraShortestPath(Spot(26018641), Spot(26018650));

	//graph.dijkstraFastestPath(Spot(26018641), Spot(26018650));

	//vector<Vertex * > vec = graph.connectingStations(Spot(26018641));

	/*if (!graph.isPathPossible(Spot(26018641), Spot(26018650))) {
	 cout << "Path is not possible" << endl;
	 return 0;
	 }*/

	//Graph graph2 = graph.getPathGraph(Spot(26018641), Spot(26018650));
	//Graph graph2 = bidirectionaldijsktra(graph, Spot(26018641), Spot(26018650));
	/*Graph graph2;

	graph2.addVertex(graph.findVertex(Spot(26018641)));
	graph2.addVertex(graph.findVertex(Spot(1271616013)));
	graph2.addVertex(graph.findVertex(Spot(390280983)));

	graph2.addVertex(graph.findVertex(Spot(1131574821)));
	graph2.addVertex(graph.findVertex(Spot(1272500941)));
	graph2.addVertex(graph.findVertex(Spot(100174630)));

	graph2.connectingStations();
	vector<Vertex *> vec2 = graph2.getVertexSet();

	for (unsigned int k = 0; k < vec2.size(); k++) {

		Vertex * vertex1 = graph2.findVertex(vec2.at(k)->getInfo());

		if (vec2.at(k)->path != nullptr) {
			Vertex * vertex2 = graph2.findVertex(vec2.at(k)->path->getInfo());

			double weight =
					sqrt(
							pow(
									vertex1->getInfo().getCoordinates_x()
											- vertex2->getInfo().getCoordinates_x(),
									2)
									+ pow(
											vertex1->getInfo().getCoordinates_y()
													- vertex2->getInfo().getCoordinates_y(),
											2));

			vertex1->addEdge(vertex2, weight, SUBWAY);
			vertex2->addEdge(vertex1, weight, SUBWAY);
		}
	}

	drawGraph(graph2, 1500, 1000);

//to stop the window from closing
	getchar();*/

	menu m;
	while (!m.terminate) {
		m.initial();
	}

	return 0;
}

