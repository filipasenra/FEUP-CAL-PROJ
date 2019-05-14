#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "Graph.h"
#include "Spot.h"
#include "Draw.h"
#include "mapParser.h"

int main() {


	//Testing draw function (no bugs found)

	Graph<Spot> myGraph;

	vector<Spot> spots;

	for (int i = 0; i < 6; i++) {
		spots.push_back(Spot(100*i + 1, 100*i + 1, 100*i + 1));
		myGraph.addVertex(spots[i]);
	}

	myGraph.addEdge(spots[1], spots[2], 2);
	myGraph.addEdge(spots[1], spots[4], 7);
	myGraph.addEdge(spots[2], spots[4], 3);
	myGraph.addEdge(spots[2], spots[5], 5);

	//drawGraph(myGraph, 600, 600);


	Graph<Spot> graph = parseMap("T11_nodes_X_Y_Aveiro.txt", "T11_edges_Aveiro.txt");


	//before drawing we have to normalize the coordenates
	drawGraph(graph, 1500, 1000);

	//to stop the window from closing
	getchar();

	return 0;
}

