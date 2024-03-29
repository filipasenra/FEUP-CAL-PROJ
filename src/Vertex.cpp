/*
 * Vertex.cpp
 *
 *  Created on: 24/05/2019
 *      Author: filip
 */

#include "Vertex.h"



Vertex::Vertex(Spot in) :
		info(in) {
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

void Vertex::addEdge(Vertex *d, double w,  TYPE_TRANSPORTATION tp) {

	adj.push_back(Edge(this, d, w, tp));
}


bool Vertex::operator<(Vertex & vertex) const {

	if(distToSource < 0)
		return dist < vertex.dist;

	return distToSource/45.0 + dist < vertex.distToSource/45.0 + vertex.dist;
}


Spot Vertex::getInfo() const {
	return this->info;
}


double Vertex::getDist() const {
	return this->dist;
}


Vertex * Vertex::getPath() const {
	return this->path;
}


vector<Edge> Vertex::getEdjes() const {
	return this->adj;
}





