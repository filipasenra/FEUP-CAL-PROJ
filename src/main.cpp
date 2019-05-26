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


	/*Graph graph = parseMap("T11_nodes_X_Y_Porto.txt", "T11_edges_Porto.txt",
			"T11_nodes_lat_lon_Porto.txt", "stcp_routes_Porto.txt", "metro_routes_Porto.txt");*/
	/*BiDirectionalDijsktra a(graph);
	a.bidirectionaldijsktrafastest(Spot(698819576), Spot(452583935));
	Graph graph2 = a.getPathGraphBi();*/

	//Graph graph2 = bidirectionaldijsktrafastest(graph, Spot(698819576), Spot(452583935));

	/*graph.dijkstraShortestPath(Spot(698819576), Spot(452583935));
	Graph graph2 = graph.getPathGraph(Spot(698819576), Spot(452583935));

	drawGraph(graph2, 1500, 1000);
	drawGraph(graph, 1500, 1000);


//to stop the window from closing
	getchar();
*/
	menu m;
	while (!m.terminate) {
		m.initial();
	}

	return 0;
}

