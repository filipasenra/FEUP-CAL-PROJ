/*
 * menu.cpp
 *
 *  Created on: 20/05/2019
 *      Author: david
 */



#include "menu.h"
#include <iostream>
#include "mapParser.h"
#include "Draw.h"


using namespace std;
menu::menu() {
	this->graph = parseMap("T11_nodes_X_Y_Aveiro.txt", "T11_edges_Aveiro.txt", "T11_nodes_lat_lon_Aveiro.txt");
}

void menu::initial(){
	// TODO Auto-generated constructor stub
	clearScreen();
	cout << endl;  //adicionar opcoes aqui
	cout << "+-----------------------------------------------------------------------+" << endl;
	cout << "|                         Initial Options Menu                          |" << endl;
	cout << "|                                                                       |" << endl;
	cout << "|      1 - Show map                                                     |" << endl;
	cout << "|      2 - find path                                                    |" << endl;
	cout << "|      3 - Exit                                                         |" << endl;
	cout << "|                                                                       |" << endl;
	cout << "+-----------------------------------------------------------------------+" << endl;

	int opcao;

	cout << "Your option: ";
	cin >> opcao;
	switch(opcao){
	case 1:
		drawGraph(graph, 1500, 1000);
		getchar();
		break;
	case 2:
		findPath();
		return;
	case 3:
		this->terminate = true;
		return;
	}

}


void menu::findPath(){
	int destino, origem;
	cout << "where are you?(node id)  " << endl;
	cin >> origem;
	cout << "where do you want to go?(node id)   " << endl;
	cin >> destino;
	this->graph.dijkstraShortestPath(Spot(origem), Spot(destino));
	this->graphPath =graph.getPathGraph(origem, destino);
	drawGraph(graphPath, 1500, 1000);
	getchar();
}





