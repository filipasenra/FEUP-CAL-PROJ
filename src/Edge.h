/*
 * Edge.h
 *
 *  Created on: 24/05/2019
 *      Author: filip
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_


enum TYPE_TRANSPORTATION{
	BUS,
	FOOT,
	SUBWAY
};

class Vertex;

/********************** Edge  ****************************/


class Edge {
	Vertex *orig;
	Vertex * dest;      // destination vertex
	bool selected;

	double weight;         // edge weight

	TYPE_TRANSPORTATION type_transportation;

public:
	Edge(Vertex *o, Vertex *d, double w);
	Edge(Vertex *o, Vertex *d, double w, TYPE_TRANSPORTATION tp);
	friend class Graph ;
	friend class Vertex ;
	bool operator<(Edge edge) const;

	// Fp07
	double getWeight() const;
	Vertex * getOrig() const;
	Vertex * getDest() const;
	TYPE_TRANSPORTATION getType_transportation(){
		return this->type_transportation;
	}

};


#endif /* SRC_EDGE_H_ */
