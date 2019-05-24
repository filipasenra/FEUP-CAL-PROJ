/*
 * Dijkstra.cpp
 *
 *  Created on: 23/05/2019
 *      Author: filip
 */

#include "Graph.h"
#include "Spot.h"
#include "MutablePriorityQueue.h"

#define VELOCITY_BUS 30 //(km/h)
#define VELOCITY_SUBWAY 40//(km/h)
#define VELOCITY_FOOT 40//(km/h)

void dijkstra(Graph * graph, const Spot & origin, const Spot & end) {

	graph->ResetNodes();

	auto s = graph->initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);

	while (!q.empty()) {

		auto v = q.extractMin();

		//Has it arrived at the end of the path?
		if (v->getInfo() == end)
			return;

		for (auto e : v->adj) {
			auto oldDist = e.getDest()->dist;

			double weight = e.getWeight();

			if(v->getInfo().hasSameSubWayStation(e.getDest()->getInfo())){
				weight /= VELOCITY_SUBWAY;
			}
			else if (v->getInfo().hasSameBusStation(e.getDest()->getInfo()))
			{
				weight /= VELOCITY_BUS;
			}
			else
			{
				weight /= VELOCITY_FOOT;
			}


			if (v->dist + weight < oldDist) {
				e.getDest()->dist = v->dist + weight;
				e.getDest()->path = v;

				if (oldDist == INF)
				q.insert(e.getDest());
				else
				q.decreaseKey(e.getDest());
			}
		}

	}

	graph->nodesReset = false;

}

