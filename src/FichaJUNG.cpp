#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

void exercicio1();
void exercicio2();
void exercicio3();

void exercicio1() {
	GraphViewer *gv = new GraphViewer(600, 600, true);

	gv->setBackground("background.jpg");

	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	int idNo = 0;
	gv->addNode(idNo);
	gv->rearrange();

	int idNo1 = 1;
	gv->addNode(idNo1);
	gv->rearrange();

	int idAresta = 0;

	gv->addEdge(idAresta, idNo, idNo1, EdgeType::UNDIRECTED);
	gv->addEdge(idAresta, idNo, idNo1, EdgeType::DIRECTED);

	//gv->removeNode(idNo);

	int idNo2 = 2;
	gv->addNode(idNo2);
	gv->rearrange();

	gv->setVertexLabel(idNo2, "Isto e um no");

	gv->setEdgeLabel(idAresta, "Isto e uma aresta");

	gv->setVertexColor(idNo, "green");

	gv->setEdgeColor(idAresta, "yellow");
}

void exercicio2() {

	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);

	gv->addNode(0, 300, 300);
	gv->addNode(1, 318, 58);
	gv->addNode(2, 325, 75);
	gv->addNode(3, 300, 100);
	gv->addNode(4, 282, 93);
	gv->addNode(5, 275, 75);

	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
	gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);

	/*for(int i = 1; ;i+=2) {

		gv->removeNode(i - 1);

		gv->addNode(i, 400, 400);

		Sleep(100);

		gv->removeNode(i);

		gv->addNode(i + 1, 300, 300);
	}*/
}

void exercicio3() {

}

int main() {
	//exercicio1();
	exercicio2();
	//exercicio3();
	getchar();
	return 0;
}
