//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "GrafoValorado.h"
#include "IndexPQ.h"
#include <vector>
class Pavimentar_City {
	public:
		/* Constructor */
		Pavimentar_City(const GrafoValorado<double> G);
		bool imposible();
		int coste_minimo();

	private:
		int weight; // coste minimo en pavimentar
		std :: vector<bool> marked; // marked[v] = true if v on tree
		std::vector <double> distTo; // distTo[w] = edgeTo[w].weight()
		std::vector <Arista<double>> edgeTo; // shortest edge from tree vertex
		IndexPQ<double> pq;						// edges with one endpoint in tree
		int V; 
		int count; // número de vértices conexas
		int coste_min;

		// add all edges e incident to v onto pq if the other endpoint has not yet been scanned
		void visit(const GrafoValorado<double>  &G, int v);
};	

