#include "Draw.h"

#include "edgetype.h"

int drawGraph(Graph<Spot> graph){

	//Displaying of the graph

	//Cria o grafo para visualização
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	vector<Vertex<Spot> *> vec = graph.getVertexSet();

	int n_edge = 0;

	for(int i = 0; i < vec.size(); i++)
	{
		Spot info = vec[i]->getInfo();
		gv->addNode(info.getId(), info.getCoordinates_x(), info.getCoordinates_y());

		vector<Edge<Spot> > outgoingEdges = vec[i]->getEdjes();

		for(int j = 0; j < outgoingEdges.size(); j++)
		{
			gv->addEdge(n_edge, outgoingEdges[j].getOrig()->getInfo().getId(), outgoingEdges[j].getDest()->getInfo().getId(), EdgeType::DIRECTED);
			n_edge++;
		}
	}

}
