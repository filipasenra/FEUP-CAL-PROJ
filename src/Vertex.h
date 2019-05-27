/*
 * Vertex.h
 *
 *  Created on: 24/05/2019
 *      Author: filip
 */

#ifndef SRC_VERTEX_H_
#define SRC_VERTEX_H_

#include "Edge.h"
#include "Spot.h"
#include <vector>
#include "MutablePriorityQueue.h"

/************************* Vertex  **************************/

class Vertex {
	Spot info;                // contents

	int queueIndex = 0; 		// required by MutablePriorityQueue
	std::vector<Vertex*> disjSet;

public:
	bool part_of_path = false;
	bool start_of_path = false;

	Vertex *path = nullptr;
	std::vector<Edge > adj;  // outgoing edges
	bool visited = false;          // auxiliary field
	double dist = 0;

	Vertex(Spot in);
	void addEdge(Vertex *dest, double w, TYPE_TRANSPORTATION tp);
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	Spot getInfo() const;
	Spot* getPointerInfo() {
		return &(this->info);
	}
	;
	double getDist() const;
	Vertex *getPath() const;
	std::vector<Edge> getEdjes() const;
	friend class Graph ;
	friend class MutablePriorityQueue<Vertex> ;
};

#endif /* SRC_VERTEX_H_ */
