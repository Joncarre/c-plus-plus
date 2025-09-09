//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <string>
#include "Arborecencia.h"
#include "GrafoDirigido.h"
using namespace std;

bool resuelve();
GrafoDirigido leerGrafo(size_t V);

// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V), por la llamada a DFS
Arborecencia::Arborecencia(GrafoDirigido const& G, size_t &raiz) : esAr(false), visitado(G.V(), false){
	size_t r = 0; // Ra�ces encontradas
	size_t k = 0; // Recordemos que 'k' es el n�mero de nodos que vamos visitando durante el DFS

	// Para tener arborescencia debe existir un v�rtice (y s�lo uno) con grado de entrada 0. Vamos a buscarlo.
	// Para ello, invertimos el grafo y miramos en todos los v�rtices, actualizando la ra�z cuando su lista de adyacencia
	// est� vac�a. 'r' nos dice cu�ntas ra�ces hemos encontrado.
	GrafoDirigido grafoInvertido(G.V());
	grafoInvertido = G.reverse();
	for (size_t i = 0; i < G.V(); i++){
		grafoInvertido.adj(i).size();
		if (grafoInvertido.adj(i).size() == 0){
			r++;
			raiz = i;
		}
	}
	if (r == 1){ // Si s�lo hemos encontrado una ra�z, en principio podr�a ser arborescente (si no tiene ciclos, por ejemplo)...
		esAr = true;
		dfs_arborecencia(G, raiz, k);
		esAr = (esAr && k == G.V()); // Si es arborescente y adem�s s�lo hemos pasado una vez por cada v�rtice, entonces 'esAr' sera true
	}
	else
		esAr = false;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
void Arborecencia::dfs_arborecencia(GrafoDirigido const& G, size_t v, size_t &k) {
	vector<size_t> lista;
	size_t w;
	++k;

	visitado[v] = true; // Marcamos el v�rtice visitado
	lista = G.adj(v); // Y obtenemos su lista de adyacencia
	while (!lista.empty()){
		w = lista.back(); // El siguiente v�rtice ser� el que est� en lista.back()
		lista.pop_back(); // Y le quitamos y de la lista
		if (visitado[w]) // Si ya lo hemos visitado...
			esAr = false; // Entonces es que hay alg�n ciclo y no es arborescente
		else 
			dfs_arborecencia(G, w, k);
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
bool Arborecencia::es_Arborecencia(){
	return esAr;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
GrafoDirigido leerGrafo(size_t V){
	GrafoDirigido grafo(V);
	size_t E, v, w;

	cin >> E;
	for (size_t i = 0; i < E; i++){
		cin >> v; cin >> w;
		grafo.ponArista(v, w);
	}
	return grafo;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
bool resuelve(){
	size_t V, raiz = 0;
	
	if (!(cin >> V))
		return false;
	GrafoDirigido grafo = leerGrafo(V);
	Arborecencia app(grafo, raiz);

	bool ok = app.es_Arborecencia();
	if (ok)
		cout << "SI " << raiz;
	else
		cout << "NO";
	cout << endl;
	return true;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	while (resuelve());
	//system("PAUSE");
	return 0;
}
