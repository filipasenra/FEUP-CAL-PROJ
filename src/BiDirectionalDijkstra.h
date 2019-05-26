/*
 * BiDirectionalDijkstra.h
 *
 *  Created on: 21/05/2019
 *      Author: filip
 */

#ifndef SRC_BIDIRECTIONALDIJKSTRA_H_
#define SRC_BIDIRECTIONALDIJKSTRA_H_


#include "Graph.h"
#include "Spot.h"
#include "MutablePriorityQueue.h"


void invertingGraph(Graph * original, Graph * final);

class BiDirectionalDijsktra: public Graph{

	Graph invertedGraph;
	Spot origin;
	Spot final;

	Spot spotFinish;
	double TotalWeight = INF;

public:
	BiDirectionalDijsktra(Graph graph){
		this->vertexSet = graph.getVertexSet();
		this->order = graph.getOrder();
		invertingGraph(&graph, &invertedGraph);
	}

	void bidirectionaldijsktra(Spot origin, Spot final);
	void bidirectionaldijsktrafastest(Spot o, Spot f);
	Graph getPathGraphBi();

};

void addingGraph(Graph * source, Graph * to_be_added);

#endif /* SRC_BIDIRECTIONALDIJKSTRA_H_ */
