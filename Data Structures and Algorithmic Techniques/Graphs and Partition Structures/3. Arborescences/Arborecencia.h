//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "GrafoDirigido.h"

class Arborecencia{
	public:
		/* Constructor */
		Arborecencia(GrafoDirigido const& G, size_t &raiz);
		bool es_Arborecencia();

	private:
		/*Atributos*/
		std::vector<bool> visitado;
		bool esAr;

		/*Funciones*/
		void dfs_arborecencia(GrafoDirigido const& G, size_t v, size_t &k);
};

