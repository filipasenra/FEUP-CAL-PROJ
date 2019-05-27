#include "Draw.h"

#include "edgetype.h"

void getMinimum(Graph graph, double & x, double & y) {

	x = INF;
	y = INF;

	vector<Vertex *> vec = graph.getVertexSet();

	for(unsigned int i = 0; i < vec.size(); i++) {

		Spot spot = vec.at(i)->getInfo();

		if(spot.getCoordinates_x() < x)
		x = spot.getCoordinates_x();

		if(spot.getCoordinates_y() < y)
		y = spot.getCoordinates_y();

	}

}

void getMaximum(Graph graph, double & x, double & y) {

	x = 0;
	y = 0;

	vector<Vertex *> vec = graph.getVertexSet();

	for (unsigned int i = 0; i < vec.size(); i++) {

		Spot spot = vec.at(i)->getInfo();

		if (spot.getCoordinates_x() > x)
			x = spot.getCoordinates_x();

		if (spot.getCoordinates_y() > y)
			y = spot.getCoordinates_y();

	}
}

int drawGraph(Graph graph, int width, int height) {

	//Displaying of the graph

	//Cria o grafo para visualização
	GraphViewer *gv = new GraphViewer(width, height, false);

	gv->createWindow(width, height);

	double x, y;
	getMinimum(graph, x, y);

	double x1, y1;
	getMaximum(graph, x1, y1);

	double graphHeight = y1 - y;
	double graphWidth = x1 - x;

	width = max((int) (height * graphWidth / graphHeight), width);

	vector<Vertex *> vec = graph.getVertexSet();
	int n_edge = 0;

	for (unsigned int i = 0; i < vec.size(); i++) {
		Spot info = vec[i]->getInfo();

		double yPercent = 1.0
				- ((info.getCoordinates_y() - y) / graphHeight * 0.9 + 0.05); //+5% to have margins
		double xPercent = (info.getCoordinates_x() - x) / graphWidth * 0.9
				+ 0.05; //*90% to be within margins

		gv->addNode(info.getId(), (int) (xPercent * width),
				(int) (yPercent * height));

		if (info.hasSubwayStop()) {
			gv->setVertexIcon(info.getId(), "images/subway.jpg");
		} else if (info.hasBusStop())
			gv->setVertexIcon(info.getId(), "images/stcp.png");

		gv->setVertexSize(info.getId(), 8);

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

int drawPath(Graph graph, int width, int height) {

	//Displaying of the graph

	//Cria o grafo para visualização
	GraphViewer *gv = new GraphViewer(width, height, false);

	gv->createWindow(width, height);

	double x, y;
	getMinimum(graph, x, y);

	double x1, y1;
	getMaximum(graph, x1, y1);

	double graphHeight = y1 - y;
	double graphWidth = x1 - x;

	width = max((int) (height * graphWidth / graphHeight), width);

	vector<Vertex *> vec = graph.getVertexSet();
	int n_edge = 0;

	for (unsigned int i = 0; i < vec.size(); i++) {
		Spot info = vec[i]->getInfo();

		double yPercent = 1.0
				- ((info.getCoordinates_y() - y) / graphHeight * 0.9 + 0.05); //+5% to have margins
		double xPercent = (info.getCoordinates_x() - x) / graphWidth * 0.9
				+ 0.05; //*90% to be within margins

		gv->addNode(info.getId(), (int) (xPercent * width),
				(int) (yPercent * height));

		if (vec.at(i)->start_of_path) {
			gv->setVertexSize(info.getId(), 40);
			gv->setVertexColor(info.getId(), GREEN);
			continue;
		} else if (vec.at(i)->part_of_path) {
			gv->setVertexSize(info.getId(), 40);
			gv->setVertexColor(info.getId(), RED);
			continue;
		}

		gv->setVertexSize(info.getId(), 8);

	}

	for (unsigned int i = 0; i < vec.size(); i++) {
		Spot info = vec[i]->getInfo();

		vector<Edge> outgoingEdges = vec[i]->getEdjes();

		for (unsigned int j = 0; j < outgoingEdges.size(); j++) {

			if (outgoingEdges.at(j).part_of_path) {
				gv->addEdge(n_edge,
						outgoingEdges[j].getOrig()->getInfo().getId(),

						outgoingEdges[j].getDest()->getInfo().getId(),
						EdgeType::DIRECTED);

				gv->setEdgeColor(n_edge, GREEN);
				gv->setEdgeThickness(n_edge, 10);

				if(outgoingEdges.at(j).getType_transportation() == SUBWAY)
					gv->setEdgeDashed(n_edge, 10);
				else if(outgoingEdges.at(j).getType_transportation() == BUS)
					gv->setEdgeThickness(n_edge, 8);

				n_edge++;
			}
		}
	}

	return 0;

}
