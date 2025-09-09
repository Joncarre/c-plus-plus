//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>
#include "Grafo.h"
using namespace std;

// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
void dfs_Aristas(Grafo const& G, size_t v, size_t &vertices, size_t &aristas, vector<bool> &marked){
	size_t w;
	++vertices;

	// IMPLEMENTACI�N CON DFS USANDO ITERADORES (el for lo usa internamente) //
	marked[v] = true;
	for (auto w : G.adj(v)){
		if (v <= w)
			aristas = aristas + 1;
		if (!marked[w]){
			dfs_Aristas(G, w, vertices, aristas, marked);
		}
	}

	// IMPLEMENTACI�N DFS USANDO VECTORES //
/*	vector<size_t> lista;
	marked[v] = true; // Marcamos que hemos pasado por el v�rtice 'v'
	lista = G.adj(v); // Hacemos una lista con los adyacenets a 'v'
	while (!lista.empty()){
		w = lista.back(); // Cogemos uno de los adyacentes a 'v'
		lista.pop_back(); // Y lo quitamos de la lista
		if (v <= w)
			aristas = aristas + 1;
		if (marked[w] == false) // Si no hemos pasado por el v�rtice 'w'...
			dfs_Aristas(G, w, vertices, aristas, marked);
	}
*/
}
//---------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V) por la llamada a la funci�n que hace el recorrido DFS
bool es_Arbol_libre(Grafo G){
	// 'aristas' es el n�mero de aristas que vamos recorriendo (y que debe ser n - 1)
	// 'vertices' es el n�mero de v�rtices que se van alcanzando a medida que avanza el DFS
	size_t vertices = 0; size_t aristas = 0;
	vector<bool> marked(G.V(), false);
	dfs_Aristas(G, 1, vertices, aristas, marked);
	// Si el n�mero de v�rtices recorridos ha alcanzado el n�mero de v�rtices del grafo y el n�mero de aristas es n - 1
	return ((vertices == G.V()) && aristas == G.V() - 1);
}
//---------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V), pues es necesario recorrer todo el grafo
Grafo leer_Grafo(size_t V){
	size_t E;
	cin >> E;

	Grafo grafoEntrada(V);
	size_t v, w;

	for (size_t i = 0; i < E; i++){
		cin >> v;
		cin >> w;
		grafoEntrada.ponArista(v, w);
	}
	return grafoEntrada;
}
//---------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
bool resuelveCaso(){
	size_t V;
	if (!(cin >> V))
		return false;

	Grafo G = leer_Grafo(V);
	bool ok = es_Arbol_libre(G);

	if (ok)
		cout << "SI" << endl;
	else
		cout << "NO" << endl;
	return true;
}
//---------------------------------------------------------------------------------------------------------
int main(){
	while (resuelveCaso());
	system("PAUSE");
	return 0;
} 
