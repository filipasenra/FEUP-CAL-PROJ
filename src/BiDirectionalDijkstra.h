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

void invertGraph(Graph * original, Graph * final);

void addingGraph(Graph * source, Graph * to_be_added);

Graph bidirectionaldijsktra(Graph graph, Spot origin, Spot final);

#endif /* SRC_BIDIRECTIONALDIJKSTRA_H_ */
