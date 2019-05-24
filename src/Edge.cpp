/*
 * Edge.cpp
 *
 *  Created on: 24/05/2019
 *      Author: filip
 */

#include "Edge.h"


Edge::Edge(Vertex *o, Vertex *d, double w) :
		orig(o), dest(d), weight(w) {
}


double Edge::getWeight() const {
	return weight;
}


Vertex * Edge::getOrig() const {
	return orig;
}


Vertex * Edge::getDest() const {
	return dest;
}


bool Edge::operator<(Edge edge) const {
	return this->getWeight() > edge.getWeight();
}





