/*
 * Edge.h
 *
 *  Created on: 24/05/2019
 *      Author: filip
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_



class Vertex;

/********************** Edge  ****************************/


class Edge {
	Vertex *orig; 	// Fp07
	Vertex * dest;      // destination vertex
	bool selected; // Fp07

	double weight;         // edge weight

public:
	Edge(Vertex *o, Vertex *d, double w);
	friend class Graph ;
	friend class Vertex ;
	bool operator<(Edge edge) const;

	// Fp07
	double getWeight() const;
	Vertex * getOrig() const;
	Vertex * getDest() const;

};


#endif /* SRC_EDGE_H_ */
