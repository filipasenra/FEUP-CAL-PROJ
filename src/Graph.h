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

using namespace std;

template<class T> class Edge;
template<class T> class Graph;
template<class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template<class T>
class Vertex {
	T info;                // contents

	Vertex<T> *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue
	vector<Vertex<T>*> disjSet;
	void addEdge(Vertex<T> *dest, double w);

public:
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;

	Vertex(T in);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	T* getPointerInfo() {
		return &(this->info);
	}
	;
	double getDist() const;
	Vertex *getPath() const;
	vector<Edge<T>> getEdjes() const;
	friend class Graph<T> ;
	friend class MutablePriorityQueue<Vertex<T>> ;
};

template<class T>
Vertex<T>::Vertex(T in) :
		info(in) {
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(this, d, w));
}

template<class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template<class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template<class T>
vector<Edge<T>> Vertex<T>::getEdjes() const {
	return this->adj;
}

/********************** Edge  ****************************/

template<class T>
class Edge {
	Vertex<T> *orig; 	// Fp07
	Vertex<T> * dest;      // destination vertex
	bool selected; // Fp07

	double weight;         // edge weight

public:
	Edge(Vertex<T> *o, Vertex<T> *d, double w);
	friend class Graph<T> ;
	friend class Vertex<T> ;
	bool operator<(Edge<T> edge) const;

	// Fp07
	double getWeight() const;
	Vertex<T> * getOrig() const;
	Vertex<T> * getDest() const;

};

template<class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w) :
		orig(o), dest(d), weight(w) {
}

template<class T>
double Edge<T>::getWeight() const {
	return weight;
}

template<class T>
Vertex<T> * Edge<T>::getOrig() const {
	return orig;
}

template<class T>
Vertex<T> * Edge<T>::getDest() const {
	return dest;
}

/*************************** Graph  **************************/

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	bool nodesReset = true;


public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addVertex(Vertex<T> * new_vertex);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;
	Graph<T> getPathGraph(const T &origin, const T &dest) const;


	// Fp05
	Vertex<T> * initSingleSource(const T &orig);
	bool relax(Vertex<T> *v, Vertex<T> *w, double weight);
	//double ** W = nullptr;   // dist
	//int **P = nullptr;   // path
	int findVertexIdx(const T &in) const;

	// Fp05 - single source
	void dijkstraShortestPath(const T &s, const T &d);
	void dijkstraShortestPathBiD(const T &s, const T &d);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
	~Graph();

	// Fp07 - minimum spanning tree
	vector<Vertex<T>*> calculatePrim();
	vector<Vertex<T>*> calculateKruskal();

	void ResetNodes();
};

template<class T>
bool Edge<T>::operator<(Edge<T> edge) const {
	return this->getWeight() > edge.getWeight();
}

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template<class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {

	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
template<class T>
int Graph<T>::findVertexIdx(const T &in) const {
	for (unsigned i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == in)
			return i;
	return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addVertex(const T &in) {
	if (findVertex(in) != nullptr)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

template<class T>
bool Graph<T>::addVertex(Vertex<T> * new_vertex) {

	if (new_vertex == NULL)
		return false;

	vertexSet.push_back(new_vertex);
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == nullptr || v2 == nullptr)
		return false;
	v1->addEdge(v2, w);
	return true;
}

/**************** Single Source Shortest Path algorithms ************/

/**
 * Initializes single source shortest path data (path, dist).
 * Receives the content of the source vertex and returns a pointer to the source vertex.
 * Used by all single-source shortest path algorithms.
 */
template<class T>
Vertex<T> * Graph<T>::initSingleSource(const T &origin) {
	for (auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}

/**
 * Analyzes an edge in single source shortest path algorithm.
 * Returns true if the target vertex was relaxed (dist, path).
 * Used by all single-source shortest path algorithms.
 */
template<class T>
inline bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	} else
		return false;
}

/**
 * Resets the nodes
 */
template<class T>
void Graph<T>::ResetNodes() {

	if (this->nodesReset)
		return;

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		vertexSet.at(i)->visited = false;
		vertexSet.at(i)->path = nullptr;
		vertexSet.at(i)->disjSet.clear();
		vertexSet.at(i)->dist = INF;
		vertexSet.at(i)->queueIndex = 0;

	}

	this->nodesReset = true;
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin, const T &end) {

	this->ResetNodes();

	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex<T>> q;
	q.insert(s);

	while (!q.empty()) {

		auto v = q.extractMin();

		//Has it arrived at the end of the path?
		if (v->info == end)
			return;

		for (auto e : v->adj) {
			auto oldDist = e.dest->dist;

			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
				q.insert(e.dest);
				else
				q.decreaseKey(e.dest);
			}
		}

	}

	this->nodesReset = false;
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const {
	vector<T> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) // missing or disconnected
	return res;
	for (; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

template<class T>
Graph<T> Graph<T>::getPathGraph(const T &origin, const T &dest) const {

	Graph<T> graph;

	vector<T> res;
	auto v = findVertex(dest);

	if (v == nullptr || v->dist == INF) // missing or disconnected
	return graph;

	Vertex<T> *old = nullptr;

	for (; v != nullptr; v = v->path) {

		graph.addVertex(v->getInfo());

		//Adding edge to new graph!!
		if (old != nullptr) {

			//let's get the weight of the edge!
			for (int i = 0; i < v->adj.size(); i++) {

				if (v->adj.at(i).getDest()->getInfo().getId()
						== old->getInfo().getId()) {
					{
						graph.addEdge(old->getInfo(), v->getInfo(),
								v->adj.at(i).getWeight());
						break;
					}
				}
			}
		}

		old = v;
	}

	return graph;
}

/**************** All Pairs Shortest Path  ***************/

template<class T>
void deleteMatrix(T **m, int n) {
	if (m != nullptr) {
		for (int i = 0; i < n; i++)
			if (m[i] != nullptr)
				delete[] m[i];
		delete[] m;
	}
}

template<class T>
Graph<T>::~Graph() {
	//deleteMatrix(W, vertexSet.size());
	//deleteMatrix(P, vertexSet.size());
}

#endif /* GRAPH_H_ */
