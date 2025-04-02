//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <limits>
#include "dijkstra.h"
#include "GrafoValorado.h"
#include "IndexPQ.h"
using namespace std;

bool resuelve();
GrafoValorado<double> leerGrafo(size_t V);
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E * logV), E por el for y logV porque actualizar en una cola con V elementos cuesta logV
dijkstra::dijkstra(const GrafoValorado<double> &grafo, int v) :
distTo(grafo.V(), numeric_limits<double>::infinity()), edgeTo(grafo.V(), Arista<double>(0, 0, 0)), pq(grafo.V()),
camino_mejor(numeric_limits<double>::infinity()), rep(0), numero(grafo.V(), 0){
	
	distTo[v] = 0.0;
	pq.push(1, 0); // Metemos el vértice 1 con prioridad 0
	numero[v] = 1;

	while (!pq.empty()){
		int vertice;
		vertice = pq.top().elem;
		pq.pop();
		for (Arista<double> arista : grafo.adj(vertice)) // Vamos a recorrer todas las aristas de 'vértice'
			relax(arista, vertice);
	}
	rep = numero[grafo.V() - 1]; // Dame el número de caminos que llegan hasta 'grafo.V() - 1'
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(logV), donde V es el número de vértices
void dijkstra::relax(const Arista<double> &arista, int v){
	int w;
	w = arista.otro(v); // Dame un adyacente a 'v'

	if (distTo[w] > distTo[v] + arista.valor()){
		numero[w] = numero[v]; // El número de caminos que llegan a 'w' es el número de camino que llegan a 'v'
		distTo[w] = distTo[v] + arista.valor(); // Y su distancia es la de 'v' + el arista que llega a 'w'
		edgeTo[w] = arista; // A 'w' se llega a través de la arista 'arista'
		pq.update(w, distTo[w]); // Actualizamos el valor de 'w' en la cola
	}
	else if (distTo[w] == distTo[v] + arista.valor()) // Si la distancia es igual...
		numero[w] += numero[v]; // El número de caminos que llegan a 'w' será el número de caminos que llegan a 'v'
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
bool dijkstra::imposible(){
	return false;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
GrafoValorado<double> leerGrafo(size_t V){
	size_t E, v, w, valor;
	GrafoValorado<double> grafo(V);

	cin >> E;
	for (size_t i = 0; i < E; i++){
		cin >> v;
		cin >> w;
		cin >> valor;
		Arista<double> arista(v, w, valor);
		grafo.ponArista(arista);
	}
	return grafo;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O()
bool resuelve(){
	size_t V;

	if (!(cin >> V))
		return false;
	GrafoValorado<double> grafo = leerGrafo(V + 1);
	dijkstra algoritmo(grafo, 1);
	cout << algoritmo.caminosCortos() << endl;
	return true;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	while (resuelve());
	//system("PAUSE");
	return 0;
}

