#include "BiDirectionalDijkstra.h"

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

		source->addVertex(invertedVertex->getInfo());
	}

	for (unsigned int i = 0; i < vec.size(); i++) {

		Vertex * vertex = vec.at(i);
		vector<Edge> edjes = vertex->getEdjes();

		for (unsigned int j = 0; j < edjes.size(); j++) {
			source->addEdge(vertex->getInfo(), edjes.at(j).getDest()->getInfo(),
					edjes.at(j).getWeight());
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
				q.decreaseKey(e.getDest());
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

Graph BiDirectionalDijsktra::getPathGraphBi() {

	Graph graph1_after = this->getPathGraph(origin, spotFinish);
	Graph graph2_after = invertedGraph.getPathGraph(final, spotFinish);

	Graph graph2_after_dir;

	invertingGraph(&(graph2_after), &(graph2_after_dir));

	//adding graph2 to 1
	addingGraph(&graph1_after, &graph2_after_dir);

	return graph1_after;

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
				q2.decreaseKey(e.getDest());
			}
		}
	}

}
