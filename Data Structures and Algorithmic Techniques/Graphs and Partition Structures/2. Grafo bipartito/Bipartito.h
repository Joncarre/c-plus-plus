//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "Grafo.h"
#include <stack>
#include <list>
class Bipartito
{

public:
	/* Constructor */
	Bipartito(Grafo const& G);
	
	bool es_bipartito();

private:

	bool esBi; // Atributo para saber si es bipartito
	std::vector<bool> color;
	std::vector<bool> marked;
	//std::vector<size_t> edgeTo; // ¡Esto no hace falta!

	void dfs_bipartito(Grafo const& G, size_t v);
};

