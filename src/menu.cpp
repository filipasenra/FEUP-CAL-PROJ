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
}

void menu::initial(){
	// TODO Auto-generated constructor stub
	clearScreen();
	this->graph = parseMap("T11_nodes_X_Y_Porto.txt", "T11_edges_Porto.txt", "T11_nodes_lat_lon_Porto.txt");
	cout << endl;  //adicionar opcoes aqui
	cout << "+-----------------------------------------------------------------------+" << endl;
	cout << "|                         Initial Options Menu                          |" << endl;
	cout << "|                                                                       |" << endl;
	cout << "|      1 - Show map                                                     |" << endl;
	cout << "|      2 - Exit                                                         |" << endl;
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
		this->terminate = false;
		return;
	}

}

