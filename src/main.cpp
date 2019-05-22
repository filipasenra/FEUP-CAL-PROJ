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


int main() {


	Graph<Spot> graph = parseMap("T11_nodes_X_Y_Aveiro.txt", "T11_edges_Aveiro.txt", "T11_nodes_lat_lon_Aveiro.txt");


	//before drawing we have to normalize the coordinates
	//drawGraph(graph, 1500, 1000);

	//graph.dijkstraShortestPath(Spot(26018641), Spot(26018648));

	//Graph<Spot> graph2 = graph.getPathGraph(26018641, 26018648);

	Graph<Spot> graph2 = bidirectionaldijsktra(graph, Spot(26018641), Spot(26018650));

	drawGraph(graph2, 1500, 1000);

	//to stop the window from closing
	getchar();


	/*menu m;
	while (!m.terminate){
		m.initial();
	}*/

	return 0;
}

