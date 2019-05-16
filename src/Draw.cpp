#include "Draw.h"

#include "edgetype.h"

double normalizingCoordenate(double inicial, double desvio, double min) {

	return (inicial - min) * desvio;
}

void getDesvio(vector<Vertex<Spot> *> vec, double &max_x, double &max_y, double &min_x, double &min_y) {

	max_x = 0, max_y = 0;
	min_x = 100000000000, min_y = 100000000000;

	for (int i = 0; i < vec.size(); i++) {
		double coordinates_x = vec.at(i)->getInfo().getCoordinates_x();
		double coordinates_y = vec.at(i)->getInfo().getCoordinates_y();

		if (coordinates_x > max_x)
			max_x = coordinates_x;

		if (coordinates_x < min_x)
			min_x = coordinates_x;

		if (coordinates_y > max_y)
			max_y = coordinates_y;

		if (coordinates_y < min_y)
			min_y = coordinates_y;
	}
}

int drawGraph(Graph<Spot> graph, int width, int height) {

	//Displaying of the graph

	//Cria o grafo para visualização
	GraphViewer *gv = new GraphViewer(width, height, false);

	gv->createWindow(width, height);

	vector<Vertex<Spot> *> vec = graph.getVertexSet();
	int n_edge = 0;
	double min_x = 0, min_y = 0, max_x = 0, max_y = 0;

	getDesvio(vec, max_x, max_y, min_x, min_y);

	//novas/velhas + desvio da origem atual da antiga
	double desvio_x = (double) width / (max_x - min_x);
	double desvio_y = (double) height / (max_y - min_y);

	for (int i = 0; i < vec.size(); i++) {
		Spot info = vec[i]->getInfo();

		gv->addNode(info.getId(),
				normalizingCoordenate(info.getCoordinates_x(), desvio_x, min_x),
				normalizingCoordenate(info.getCoordinates_y(), desvio_y,
						min_y));

		vector<Edge<Spot> > outgoingEdges = vec[i]->getEdjes();

		for (int j = 0; j < outgoingEdges.size(); j++) {

			gv->addEdge(n_edge, outgoingEdges[j].getOrig()->getInfo().getId(),
					outgoingEdges[j].getDest()->getInfo().getId(),
					EdgeType::DIRECTED);


			gv->setEdgeLabel(n_edge, to_string(outgoingEdges[j].getWeight()));
			n_edge++;
		}
	}

}
