//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <vector>

using namespace std;

class RepartiendoPaquetes{
	public:
		/* Constructor */

		RepartiendoPaquetes(const GrafoDirigidoValorado<double> &G, int s);
		vector <double> oficina_to_Home(){ return distTo; }  //distancia de la oficina a todas las casas

		bool imposible();

	private:

		vector <double> distTo;	// distTo[w] = edgeTo[w].weight()
		vector <AristaDirigida<double>> edgeTo; // shortest edge from tree vertex
		IndexPQ<double> pq; // edges with one endpoint in tree
		void relax(const AristaDirigida<double> &e);
};



