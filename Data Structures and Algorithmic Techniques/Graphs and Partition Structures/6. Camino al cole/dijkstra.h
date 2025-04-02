//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "GrafoValorado.h"
#include "IndexPQ.h"
#include <vector>

using namespace std;

class dijkstra{
	public:
		/* Constructor */
		dijkstra(const GrafoValorado<double> &G, int s);
		vector <double> oficina_to_Home(){ return distTo; } // distancia de la oficina a todas las casas

		bool imposible();
		/*
		devuelve el numero de caminos minimos desde el primer al ultimo vertice.
		O(1)
		*/
		int caminosCortos(){ return rep; }
	
	private:

		vector <double> distTo;	// distTo[w] = edgeTo[w].weight()
		vector <Arista<double>> edgeTo;	// shortest edge from tree vertex
		IndexPQ<double> pq; // edges with one endpoint in tree
		double camino_mejor;
		int rep;										
		vector<int> numero; // guarda el número de caminos mínimos de cada vértice
		void relax(const Arista<double> &e , int v );
};	

