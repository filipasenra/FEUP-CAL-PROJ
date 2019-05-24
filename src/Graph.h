/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "MutablePriorityQueue.h"
#include <iostream>
#include "Spot.h"
#include "Edge.h"
#include "Vertex.h"
#include <map>

using namespace std;


#define INF std::numeric_limits<double>::max()


/*************************** Graph  **************************/


class Graph {
	vector<Vertex *> vertexSet;    // vertex set


	map <unsigned int, unsigned int> order; //look up table

public:

	bool nodesReset = true;

	Vertex *findVertex(const Spot &in) const;
	bool addVertex(const Spot &in);
	bool addVertex(Vertex * new_vertex);
	bool addEdge(const Spot &sourc, const Spot &dest, double w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;
	Graph getPathGraph(const Spot &origin, const Spot &dest) const;


	Vertex * initSingleSource(const Spot &orig);
	bool relax(Vertex *v, Vertex *w, double weight);
	int findVertexIdx(const Spot &in) const;
	void dfs(Spot & origin);
	void bfs(Spot & origin);
	void visitDFS(Vertex * vertex);
	bool isPathPossible(const Spot & origin, const Spot & end);


	void dijkstraShortestPath(const Spot &s, const Spot &d);
	vector<Spot> getPath(const Spot &origin, const Spot &dest) const;
	void dijkstraFastestPath(const Spot & origin, const Spot & end);

	~Graph();

	void ResetNodes();
};



#endif /* GRAPH_H_ */
