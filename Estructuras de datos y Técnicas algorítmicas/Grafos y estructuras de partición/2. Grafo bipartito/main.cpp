//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include "Bipartito.h"
#include "Grafo.h"
using namespace std;

bool resuelve();
Grafo leerGrafo(size_t V);
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V), por la llamada a DFS
Bipartito::Bipartito(Grafo const& G) : /*edgeTo(G.V()),*/ color(G.V()), marked(G.V(), false), esBi(true){
	for (size_t v = 0; v < G.V(); v++){ // Este for se usa por si el grafo tiene más de una componente conexa
		if (!marked[v]){ // Si el vértice desde el cual vas a comenzar el DFS no ha sido marcado... (también por las posibles componentes conexas)
			color[v] = true; // Se pone a 'false' por poner algo, también podría ponerse a 'true
			dfs_bipartito(G, v);
		}
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V), donde E es el número de aristas y V el de vértices
void Bipartito::dfs_bipartito(Grafo const& grafo, size_t v){
	marked[v] = true;
	for (auto w : grafo.adj(v)) {
		if (!marked[w]){ // ¿Ya hemos pasado por el vértice 'w'?
			// edgeTo[w] = v; // A 'w' se llega a través de 'v' // ¡Nótese que esto no hace falta!
			color[w] = !color[v]; // Como 'v' y 'w' están "juntos", sus colores deben ser distintos
			dfs_bipartito(grafo, w); // Llamada recursiva desde el nuevo vértice, es decir, desde 'w'
		}
		else if (color[w] == color[v]) { // Si 'v' y 'w' (adyacentes) tienen el mismo color...
			esBi = false; // No es bipartito
			return;
		}
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
bool Bipartito::es_bipartito(){
	return esBi;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
Grafo leerGrafo(size_t V){
	size_t E;
	cin >> E;
	Grafo grafo(V);
	size_t v, w;

	for (size_t i = 0; i < E; i++){
		cin >> v; cin >> w;
		grafo.ponArista(v, w);
	}
	return grafo;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
bool resuelve(){
	size_t V;
	if (!(cin >> V))
		return false;
	
	Grafo grafo = leerGrafo(V);
	Bipartito bi(grafo);
	
	bool ok = bi.es_bipartito();

	if (ok) 
		cout << "SI" << endl;
	else 
		cout << "NO" << endl;
	return true;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	while (resuelve());
	//system("PAUSE");
	return 0;
}
