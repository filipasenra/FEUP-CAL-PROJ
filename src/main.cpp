#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

#include "Graph.h"
#include "Spot.h"
#include "Draw.h"

int main() {


	//Testing draw function (no bugs found)

	Graph<Spot> myGraph;

	vector<Spot> spots;

	for (int i = 0; i < 6; i++) {
		spots.push_back(Spot(100*i + 1, 100*i + 1, 100*i + 1, Type::FOOT));
		myGraph.addVertex(spots[i]);

		cout << "id: " << spots[i].getId() << " x: " << spots[i].getCoordinates_x() << " y: " << spots[i].getCoordinates_y() << endl;
	}

	myGraph.addEdge(spots[1], spots[2], 2);
	myGraph.addEdge(spots[1], spots[4], 7);
	myGraph.addEdge(spots[2], spots[4], 3);
	myGraph.addEdge(spots[2], spots[5], 5);

	drawGraph(myGraph);

	getchar();

	return 0;
}

