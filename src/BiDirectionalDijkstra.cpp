
/*
 * BiDirectionalDijkstra.cpp
 *
 *	contain all the algorithm used in the project
 */

#include "BiDirectionalDijkstra.h"

#include "Draw.h"
#include "Utilities.h"

void invertingGraph(Graph * original, Graph * final) {

	vector<Vertex *> vec = original->getVertexSet();

	for (unsigned int i = 0; i < vec.size(); i++) {

		Vertex * invertedVertex = vec.at(i);

		final->addVertex(invertedVertex->getInfo());
	}

	//Inverting edges

	for (unsigned int i = 0; i < vec.size(); i++) {

		Vertex* vertex = vec.at(i);
		vector<Edge> edjes = vertex->getEdjes();

		for (unsigned int j = 0; j < edjes.size(); j++) {

			final->addEdge(edjes.at(j).getDest()->getInfo(), vertex->getInfo(),
					edjes.at(j).getWeight());
		}
	}

}

void addingGraph(Graph * source, Graph * to_be_added) {

	vector<Vertex *> vec = to_be_added->getVertexSet();

	for (unsigned int i = 0; i < vec.size(); i++) {

		Vertex * invertedVertex = vec.at(i);

		if (invertedVertex->part_of_path)
			source->findVertex(invertedVertex->getInfo())->part_of_path = true;

		if (invertedVertex->start_of_path)
			source->findVertex(invertedVertex->getInfo())->start_of_path = true;
	}

	for (unsigned int i = 0; i < vec.size(); i++) {

		Vertex * vertex = vec.at(i);
		vector<Edge> edjes = vertex->getEdjes();

		for (unsigned int j = 0; j < edjes.size(); j++) {

			//Checks if edje is part of the path
			if (!edjes.at(j).part_of_path)
				continue;

			//If it is than lets find it's opositive and transform it into a path edje

			//Vertex of origin in original graph
			Vertex * vertexOposite = source->findVertex(
					edjes.at(j).getDest()->getInfo());

			for (unsigned int k = 0; k < vertexOposite->adj.size(); k++) {

				if (vertexOposite->adj.at(k).getDest()->getInfo()
						== vertex->getInfo()) {
					vertexOposite->adj.at(k).part_of_path = true;
					break;
				}
			}
		}
	}

}

void BiDirectionalDijsktra::bidirectionaldijsktra(Spot o, Spot f) {

	origin = o;
	final = f;

	spotFinish = final;
	TotalWeight = INF;

	//Original graph
	this->ResetNodes();
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);

	//Inverted Graph
	invertedGraph.ResetNodes();
	auto s2 = invertedGraph.initSingleSource(final);
	MutablePriorityQueue<Vertex> q2;
	q2.insert(s2);

	while (!q.empty() && !q2.empty()) {

		//Normal Graph

		auto v = q.extractMin();
		auto v2 = q2.extractMin();

		double totalWeightTmp = v->getDist() + v2->getDist();

		if (totalWeightTmp >= TotalWeight) {
			break;
		}

		//Has it arrived at the end of the path?
		if (v->getInfo() == final) {
			spotFinish = v->getInfo();
			break;
		}

		if (invertedGraph.findVertex(v->getInfo())->getDist() != INF) {

			double totalWeightTmp = findVertex(v->getInfo())->getDist()
			+ invertedGraph.findVertex(v->getInfo())->getDist();

			if (TotalWeight > totalWeightTmp) {
				TotalWeight = totalWeightTmp;
				spotFinish = v->getInfo();

			}
		}

		for (auto e : v->adj) {
			auto oldDist = e.getDest()->getDist();

			if (relax(v, e.getDest(), e.getWeight())) {
				if (oldDist == INF)
				q.insert(e.getDest());
				else
				{
					if(e.dest->queueIndex != 0)
					q.decreaseKey(e.getDest());
				}
			}
		}

		//Inverted Graph

		//Has it arrived at the end of the path?
		if (v2->getInfo() == origin) {
			spotFinish = v2->getInfo();
			break;
		}

		if (findVertex(v2->getInfo())->getDist() != INF) {

			double totalWeightTmp = findVertex(v2->getInfo())->getDist()
			+ invertedGraph.findVertex(v2->getInfo())->getDist();

			if (TotalWeight > totalWeightTmp) {
				TotalWeight = totalWeightTmp;
				spotFinish = v2->getInfo();
			}
		}

		for (auto e : v2->adj) {
			auto oldDist = e.getDest()->getDist();

			if (invertedGraph.relax(v2, e.getDest(), e.getWeight())) {
				if (oldDist == INF)
				q2.insert(e.getDest());
				else
				q2.decreaseKey(e.getDest());
			}
		}
	}

}

void BiDirectionalDijsktra::getPathGraphBi() {

	this->getPathGraph(origin, spotFinish);
	invertedGraph.getPathGraph(final, spotFinish);

	addingGraph(this, &invertedGraph);

	this->findVertex(spotFinish)->start_of_path = false;

}

void BiDirectionalDijsktra::bidirectionaldijsktrafastest(Spot o, Spot f) {

	origin = o;
	final = f;

	spotFinish = final;
	TotalWeight = INF;

	//Original graph
	this->ResetNodes();
	auto s = this->initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);

	//Inverted Graph
	invertedGraph.ResetNodes();
	auto s2 = invertedGraph.initSingleSource(final);
	MutablePriorityQueue<Vertex> q2;
	q2.insert(s2);

	while (!q.empty() && !q2.empty()) {

		//Normal Graph

		auto v = q.extractMin();
		auto v2 = q2.extractMin();

		double totalWeightTmp = v->getDist() + v2->getDist();

		if (totalWeightTmp >= TotalWeight) {
			break;
		}

		//Has it arrived at the end of the path?
		if (v->getInfo() == final) {
			spotFinish = v->getInfo();
			break;
		}

		if (invertedGraph.findVertex(v->getInfo())->getDist() != INF) {

			double totalWeightTmp = this->findVertex(v->getInfo())->getDist()
			+ invertedGraph.findVertex(v->getInfo())->getDist();

			if (TotalWeight > totalWeightTmp) {
				TotalWeight = totalWeightTmp;
				spotFinish = v->getInfo();

			}
		}

		for (auto e : v->adj) {
			auto oldDist = e.getDest()->getDist();

			if (this->relaxFastest(v, e.getDest(), e.getWeight())) {
				if (oldDist == INF)
				q.insert(e.getDest());
				else
				q.decreaseKey(e.getDest());
			}
		}

		//Inverted Graph

		//Has it arrived at the end of the path?
		if (v2->getInfo() == origin) {
			spotFinish = v2->getInfo();
			break;
		}

		if (this->findVertex(v2->getInfo())->getDist() != INF) {

			double totalWeightTmp = this->findVertex(v2->getInfo())->getDist()
			+ invertedGraph.findVertex(v2->getInfo())->getDist();

			if (TotalWeight > totalWeightTmp) {
				TotalWeight = totalWeightTmp;
				spotFinish = v2->getInfo();
			}
		}

		for (auto e : v2->adj) {
			auto oldDist = e.getDest()->getDist();

			if (invertedGraph.relaxFastest(v2, e.getDest(), e.getWeight())) {
				if (oldDist == INF)
				q2.insert(e.getDest());
				else
				{
					if(e.dest->queueIndex != 0)
					q2.decreaseKey(e.getDest());
				}
			}
		}
	}

}

void BiDirectionalDijsktra::bidirectionalAStar(const Spot &s, const Spot &d) {

	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		vertexSet.at(i)->distToSource = distanceCoordinates(
				vertexSet.at(i)->getInfo(), d);
	}

	bidirectionaldijsktrafastest(s, d);

}
