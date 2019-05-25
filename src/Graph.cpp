/*
 * Graph.cpp
 *
 *  Created on: 24/05/2019
 *      Author: filip
 */

#define VELOCITY_BUS 30 //(km/h)
#define VELOCITY_SUBWAY 40//(km/h)
#define VELOCITY_FOOT 40//(km/h)

#include "Graph.h"
#include "Math.h"
#include "Stack"

int Graph::getNumVertex() const {
	return vertexSet.size();
}

vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(const Spot &in) const {

	map<unsigned int, unsigned int>::const_iterator it1 = order.find(
			in.getId());

	if (it1 == order.end())
		return nullptr;

	return vertexSet.at(it1->second);
}

/*
 * Finds the index of the vertex with a given content.
 */

int Graph::findVertexIdx(const Spot &in) const {
	map<unsigned int, unsigned int>::const_iterator it1 = order.find(
			in.getId());

	if (it1 == order.end())
		return -1;

	return it1->second;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addVertex(const Spot &in) {
	if (findVertex(in) != nullptr)
		return false;

	order.insert(
			pair<unsigned int, unsigned int>(in.getId(), vertexSet.size()));

	vertexSet.push_back(new Vertex(in));

	return true;
}

bool Graph::addVertex(Vertex * new_vertex) {

	if (new_vertex == NULL)
		return false;

	order.insert(
			pair<unsigned int, unsigned int>(new_vertex->getInfo().getId(),
					vertexSet.size()));

	vertexSet.push_back(new_vertex);
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const Spot &sourc, const Spot &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == nullptr || v2 == nullptr)
		return false;
	v1->addEdge(v2, w, FOOT);
	return true;
}

/**************** Single Source Shortest Path algorithms ************/

/**
 * Initializes single source shortest path data (path, dist).
 * Receives the content of the source vertex and returns a pointer to the source vertex.
 * Used by all single-source shortest path algorithms.
 */

Vertex * Graph::initSingleSource(const Spot &origin) {
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

inline bool Graph::relax(Vertex *v, Vertex *w, double weight) {
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

void Graph::ResetNodes() {

	if (this->nodesReset)
		return;

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		vertexSet.at(i)->visited = false;
		vertexSet.at(i)->path = nullptr;
		vertexSet.at(i)->disjSet.clear();
		vertexSet.at(i)->dist = INF;
		vertexSet.at(i)->queueIndex = 0;
		vertexSet.at(i)->visited = false;

	}

	this->nodesReset = true;
}

void Graph::dijkstraShortestPath(const Spot &origin, const Spot &end) {

	this->ResetNodes();

	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
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

vector<Spot> Graph::getPath(const Spot &origin, const Spot &dest) const {
	vector<Spot> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) // missing or disconnected
	return res;
	for (; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}

Graph Graph::getPathGraph(const Spot &origin, const Spot &dest) const {

	Graph graph;

	vector<Spot> res;
	auto v = findVertex(dest);

	if (v == nullptr || v->dist == INF) // missing or disconnected
	return graph;

	Vertex *old = nullptr;

	for (; v != nullptr; v = v->path) {

		graph.addVertex(v->getInfo());

		//Adding edge to new graph!!
		if (old != nullptr) {

			//let's get the weight of the edge!
			for (unsigned int i = 0; i < v->adj.size(); i++) {

				if (v->adj.at(i).getDest()->getInfo().getId()
						== old->getInfo().getId()) {
					{
						graph.addEdge(old->getInfo(), v->getInfo(),
								v->adj.at(i).getWeight());
						graph.addEdge(v->getInfo(), old->getInfo(),
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

void Graph::visitDFS(Vertex * vertex) {

	vertex->visited = true;

	vector<Edge> vec = vertex->adj;

	for (unsigned int i = 0; i < vec.size(); i++) {

		if (vec.at(i).dest->visited)
			continue;

		visitDFS(vec.at(i).dest);
	}
}

void Graph::dfs(Spot & origin) {

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {

		vertexSet.at(i)->visited = false;
	}

	Vertex * vertex = this->findVertex(origin);

	if (vertex == NULL)
		return;

	visitDFS(vertex);
}

void Graph::bfs(Spot & origin) {

	for (int i = 0; i < this->vertexSet.size(); i++) {

		vertexSet.at(i)->visited = false;
	}

	MutablePriorityQueue<Vertex> q;
	Vertex * begin = this->findVertex(origin);
	q.insert(begin);
	begin->visited = true;

	while (!q.empty()) {
		Vertex * vertex = q.extractMin();

		vector<Edge> edjes = vertex->adj;

		for (unsigned int i = 0; i < edjes.size(); i++) {
			if (edjes.at(i).dest->visited)
				continue;

			edjes.at(i).dest->visited = true;
			q.insert(edjes.at(i).dest);
		}

	}

}

bool Graph::isPathPossible(const Spot & origin, const Spot & end) {

	for (int i = 0; i < this->vertexSet.size(); i++) {

		vertexSet.at(i)->visited = false;
	}

	MutablePriorityQueue<Vertex> q;
	Vertex * begin = this->findVertex(origin);
	q.insert(begin);
	begin->visited = true;

	while (!q.empty()) {
		Vertex * vertex = q.extractMin();

		vector<Edge> edjes = vertex->adj;

		for (unsigned int i = 0; i < edjes.size(); i++) {

			if (edjes.at(i).dest->getInfo() == end)
				return true;

			if (edjes.at(i).dest->visited)
				continue;

			edjes.at(i).dest->visited = true;
			q.insert(edjes.at(i).dest);
		}

	}

	return false;

}

void Graph::dijkstraFastestPath(const Spot & origin, const Spot & end) {

	this->ResetNodes();

	auto s = initSingleSource(origin);
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

			if (v->getInfo().hasSameSubWayStation(e.getDest()->getInfo())) {
				weight /= VELOCITY_SUBWAY;
			} else if (v->getInfo().hasSameBusStation(e.getDest()->getInfo())) {
				weight /= VELOCITY_BUS;
			} else {
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

	this->nodesReset = false;

}

bool Graph::relaxPrim(Vertex *v, Vertex *w) {

	double weight = sqrt(
			pow(
					v->getInfo().getCoordinates_x()
							- w->getInfo().getCoordinates_x(), 2)
					+ pow(
							v->getInfo().getCoordinates_y()
									- w->getInfo().getCoordinates_y(), 2));

	if (v->dist + weight < w->dist) {
		{
			w->dist = v->dist + weight;
			w->path = v;

			cout << v->getInfo().getId() << " " << w->getInfo().getId() << endl;

			return true;
		}
	} else {
		return false;
	}
}

vector<Vertex *> Graph::connectingStations() {

	vector<Vertex *> mst;

	if (this->getNumVertex() == 0)
		return mst;

	for (auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
		v->visited = false;
	}

	Vertex * s = this->vertexSet.at(0);
	s->visited = true;

	stack<Vertex *> first;
	first.push(s);
	stack<Vertex *> second;
	second.push(s);

	while (!first.empty() && !second.empty()) {

		Vertex * vertex1 = first.top();
		Vertex * vertex2 = second.top();

		double weightFirst = INF;
		Vertex * vertex_first;

		for (unsigned int i = 0; i < vertexSet.size(); i++) {

			Vertex * vertexToBeAnalized = vertexSet.at(i);

			if (vertexToBeAnalized->getInfo() == vertex1->getInfo()) {
				continue;
			}

			if(vertexToBeAnalized->visited)
				continue;

			double weight =
					sqrt(
							pow(
									vertex1->getInfo().getCoordinates_x()
											- vertexToBeAnalized->getInfo().getCoordinates_x(),
									2)
									+ pow(
											vertex1->getInfo().getCoordinates_y()
													- vertexToBeAnalized->getInfo().getCoordinates_y(),
											2));

			if (weight < weightFirst) {
				weightFirst = weight;
				vertex_first = vertexToBeAnalized;
			}
		}

		double weightSecond = INF;
		Vertex * vertex_second;

		for (unsigned int i = 0; i < vertexSet.size(); i++) {

			Vertex * vertexToBeAnalized = vertexSet.at(i);

			if (vertexToBeAnalized->getInfo() == vertex2->getInfo()) {
				continue;
			}

			if(vertexToBeAnalized->visited)
				continue;

			double weight =
					sqrt(
							pow(
									vertex2->getInfo().getCoordinates_x()
											- vertexToBeAnalized->getInfo().getCoordinates_x(),
									2)
									+ pow(
											vertex2->getInfo().getCoordinates_y()
													- vertexToBeAnalized->getInfo().getCoordinates_y(),
											2));

			if (weight < weightSecond) {
				weightSecond = weight;
				vertex_second = vertexToBeAnalized;
			}
		}

		if (weightFirst == INF && weightSecond == INF)
		{
			break;
		}

		if (weightFirst < weightSecond) {

			first.push(vertex_first);
			first.top()->path = vertex1;
			first.top()->dist = weightFirst;
			second.top()->visited = true;
		} else {

			second.push(vertex_second);
			second.top()->path = vertex2;
			second.top()->dist = weightSecond;
			second.top()->visited = true;
		}

	}

	return mst;

}

Graph::~Graph() {
//deleteMatrix(W, vertexSet.size());
//deleteMatrix(P, vertexSet.size());
}

