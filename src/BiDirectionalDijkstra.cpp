#include "BiDirectionalDijkstra.h"

void invertGraph(Graph * original, Graph * final) {

	vector<Vertex *> vec = original->getVertexSet();

	for (int i = 0; i < vec.size(); i++) {

		Vertex * invertedVertex = vec.at(i);

		final->addVertex(invertedVertex->getInfo());
	}

	//Inverting edges

	for (int i = 0; i < vec.size(); i++) {

		Vertex* vertex = vec.at(i);
		vector<Edge> edjes = vertex->getEdjes();

		for (int j = 0; j < edjes.size(); j++) {

			final->addEdge(edjes.at(j).getDest()->getInfo(), vertex->getInfo(),
					edjes.at(j).getWeight());
		}
	}

}

void addingGraph(Graph * source, Graph * to_be_added) {

	vector<Vertex *> vec = to_be_added->getVertexSet();

	for (int i = 0; i < vec.size(); i++) {

		Vertex * invertedVertex = vec.at(i);

		source->addVertex(invertedVertex->getInfo());
	}

	for (int i = 0; i < vec.size(); i++) {

		Vertex * vertex = vec.at(i);
		vector<Edge> edjes = vertex->getEdjes();

		for (int j = 0; j < edjes.size(); j++) {
			source->addEdge(vertex->getInfo(), edjes.at(j).getDest()->getInfo(),
					edjes.at(j).getWeight());
		}
	}

}

Graph bidirectionaldijsktra(Graph graph, Spot origin, Spot final) {

	Graph invertedGraph;

	invertGraph(&graph, &invertedGraph);

	//BIDIRECTIONAL

	//Original graph
	graph.ResetNodes();
	auto s = graph.initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);

	//Inverted Graph
	invertedGraph.ResetNodes();
	auto s2 = invertedGraph.initSingleSource(final);
	MutablePriorityQueue<Vertex> q2;
	q2.insert(s2);

	Spot spotFinish = final;
	double TotalWeight = INF;

	while (!q.empty() && !q2.empty()) {

		//Normal Graph

		auto v = q.extractMin();

		//Has it arrived at the end of the path?
		if (v->getInfo() == final) {
			spotFinish = v->getInfo();
			break;
		}

		if (invertedGraph.findVertex(v->getInfo())->getDist() != INF) {

			double totalWeightTmp = graph.findVertex(v->getInfo())->getDist()
					+ invertedGraph.findVertex(v->getInfo())->getDist();

			if (TotalWeight > totalWeightTmp) {
				TotalWeight = totalWeightTmp;
				spotFinish = v->getInfo();

			} else {
				break;
			}
		}

		for (auto e : v->adj) {
			auto oldDist = e.getDest()->getDist();

			if (graph.relax(v, e.getDest(), e.getWeight())) {
				if (oldDist == INF)
				q.insert(e.getDest());
				else
				q.decreaseKey(e.getDest());
			}
		}

		//Inverted Graph

		auto v2 = q2.extractMin();

		//Has it arrived at the end of the path?
		if (v2->getInfo() == origin) {
			spotFinish = v2->getInfo();
			break;
		}

		if (graph.findVertex(v2->getInfo())->getDist() != INF) {

			double totalWeightTmp = graph.findVertex(v2->getInfo())->getDist()
					+ invertedGraph.findVertex(v2->getInfo())->getDist();

			if (TotalWeight > totalWeightTmp) {

				TotalWeight = totalWeightTmp;
				spotFinish = v2->getInfo();
			} else {
				break;
			}
		}

		for (auto e : v2->adj) {
			auto oldDist = e.getDest()->getDist();

			if (graph.relax(v2, e.getDest(), e.getWeight())) {
				if (oldDist == INF)
				q2.insert(e.getDest());
				else
				q2.decreaseKey(e.getDest());
			}
		}

	}

	//getting path
	Graph graph1_after = graph.getPathGraph(origin, spotFinish);
	Graph graph2_after = invertedGraph.getPathGraph(final, spotFinish);

	Graph graph2_after_dir;

	invertGraph(&(graph2_after), &(graph2_after_dir));

	//adding graph2 to 1
	addingGraph(&graph1_after, &graph2_after_dir);

	cout << graph1_after.getVertexSet().size();

	return graph1_after;

}
