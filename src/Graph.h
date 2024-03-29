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

protected:
	vector<Vertex *> vertexSet;    // vertex set
	map <unsigned int, unsigned int> order; //look up table

public:

	bool nodesReset = true;

	Vertex *findVertex(const Spot &in) const;
	bool addVertex(const Spot &in);
	bool addVertex(Vertex * new_vertex);
	bool addEdge(const Spot &sourc, const Spot &dest, double w, TYPE_TRANSPORTATION type = FOOT);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;

	map <unsigned int, unsigned int> getOrder(){
		return this->order;
	};
	void getPathGraph(const Spot &origin, const Spot &dest) const;


	Vertex * initSingleSource(const Spot &orig);
	bool relax(Vertex *v, Vertex *w, double weight);
	bool relaxFastest(Vertex *v, Vertex *w, double weight);
	int findVertexIdx(const Spot &in) const;
	void dfs(Spot & origin);
	void bfs(Spot & origin);
	void visitDFS(Vertex * vertex);
	bool isPathPossible(const Spot & origin, const Spot & end);
	vector<Vertex *> connectingStations();
	bool relaxPrim(Vertex *v, Vertex *w);

	void dijkstraShortestPath(const Spot &s, const Spot &d);
	vector<Spot> getPath(const Spot &origin, const Spot &dest) const;
	void resetPath() const;
	void dijkstraFastestPath(const Spot & origin, const Spot & end);
	void AStar(const Spot &s, const Spot &d);

	~Graph();

	void ResetNodes();
};



#endif /* GRAPH_H_ */
