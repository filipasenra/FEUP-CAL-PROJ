#include "Draw.h"

#include "edgetype.h"

int drawGraph(Graph graph, int width, int height) {

	//Displaying of the graph

	//Cria o grafo para visualização
	GraphViewer *gv = new GraphViewer(width, height, false);

	gv->createWindow(width, height);

	vector<Vertex *> vec = graph.getVertexSet();
	int n_edge = 0;

	Spot first = vec[0]->getInfo();

	for (unsigned int i = 0; i < vec.size(); i++) {
		Spot info = vec[i]->getInfo();

		gv->addNode(info.getId(),
				info.getCoordinates_x() - first.getCoordinates_x(),
				info.getCoordinates_y() - first.getCoordinates_y());

		if (info.hasSubwayStop()) {
			gv->setVertexIcon(info.getId(), "images/subway.jpg");
		} else if (info.hasBusStop())
			gv->setVertexIcon(info.getId(), "images/stcp.png");
	}

	for (unsigned int i = 0; i < vec.size(); i++) {
		Spot info = vec[i]->getInfo();

		vector<Edge> outgoingEdges = vec[i]->getEdjes();

		for (unsigned int j = 0; j < outgoingEdges.size(); j++) {

			if (graph.findVertexIdx(outgoingEdges[j].getOrig()->getInfo())
					< graph.findVertexIdx(
							outgoingEdges[j].getDest()->getInfo()))

							{
				gv->addEdge(n_edge,
						outgoingEdges[j].getOrig()->getInfo().getId(),

						outgoingEdges[j].getDest()->getInfo().getId(),
						EdgeType::UNDIRECTED);

				n_edge++;
			}
		}
	}

	return 0;

}
