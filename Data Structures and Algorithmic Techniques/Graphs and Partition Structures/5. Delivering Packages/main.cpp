//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <limits>
#include <string>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include "RepartiendoPaquetes.h"
using namespace std;

bool resuelve();
GrafoDirigidoValorado<double> leerGrafo(size_t V);
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E log V), donde E es el número de aristas y V el de vértices
RepartiendoPaquetes::RepartiendoPaquetes(const GrafoDirigidoValorado<double> &grafo, int s) :
distTo(grafo.V(), numeric_limits<double>::infinity()), edgeTo(grafo.V(), AristaDirigida<double>(0, 0, 0)), pq(grafo.V()) {
	distTo[s] = 0.0;
	pq.push(1, 0); // Metemos el vértice 1 con prioridad 0
	while (!pq.empty()){
		int vertice;
		vertice = pq.top().elem;
		pq.pop();
		for (AristaDirigida<double> e : grafo.adj(vertice))
			relax(e);
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(log V), la mayor complejidad viene del update que hacemos en la cola 'pq'
void RepartiendoPaquetes::relax(const AristaDirigida<double> &e){
	// Al pasarle la arista, tenemos que coger su vértice origen (from) y su vértice destino (to)
	int v = e.from();
	int w = e.to();
	// Si la distancia hasta 'w' era mayor que la que hay hasta 'v' + el valor 
	// de la arista que va desde 'v' a 'w'
	if (distTo[w] > distTo[v] + e.valor()){
		distTo[w] = distTo[v] + e.valor();
		edgeTo[w] = e; // Ponemos la nueva arista que llega a 'w'
		pq.update(w, distTo[w]); // Actualizamos el nuevo coste de 'w' en la pila
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
bool RepartiendoPaquetes::imposible(){
	return false;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
GrafoDirigidoValorado<double> leerGrafo(size_t V){
	size_t E, v, w, valor;
	GrafoDirigidoValorado<double> grafo(V);

	cin >> E;
	for (size_t i = 0; i < E; i++){
		cin >> v;
		cin >> w;
		cin >> valor;
		AristaDirigida<double> arista(v, w, valor);
		grafo.ponArista(arista);
	}
	return grafo;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E log V)
bool resuelve(){
	size_t V, oficina, paquetes, destino_iesimo, solucion = 0;

	if (!(cin >> V))
		return false;
	GrafoDirigidoValorado<double> grafo = leerGrafo(V + 1);

	vector<double> destinos; // Vector que almacenará todos los destinos de los paquetes
	cin >> oficina;
	cin >> paquetes;
	for (size_t i = 0; i < paquetes; i++){
		cin >> destino_iesimo;
		destinos.push_back(destino_iesimo);
	}

	RepartiendoPaquetes ida(grafo, oficina);
	vector<double> esfuerzoIda;
	esfuerzoIda = ida.oficina_to_Home();

	GrafoDirigidoValorado<double> grafoInverso = grafo.reverse(); // Invertimos el grado para averiguar los costes del camino de vuelta

	RepartiendoPaquetes vuelta(grafoInverso, oficina);
	vector<double> esfuerzoVuelta;
	esfuerzoVuelta = vuelta.oficina_to_Home();

	bool imposible = false;
	for (size_t i = 0; i < destinos.size(); i++){
		// Vamos acumulando el coste de lo que cuesta ir hasta el vértice i-ésimo y volver (o sea, vértice por vértice)
		solucion += esfuerzoIda[destinos.at(i)] + esfuerzoVuelta[destinos.at(i)];
		// Si alguno de los caminos es infinito, entonces es que no se ha podido alcanzar ese vértice con el grafo dado 
		// (por ejemplo, porque no existe una arista para llegar hasta él, como ocurre con la segunda entrada)
		if (esfuerzoIda[destinos.at(i)] == numeric_limits<double>::infinity() ||
			esfuerzoVuelta[destinos.at(i)] == numeric_limits<double>::infinity())
			imposible = true;
	}
	if (imposible)
		cout << "Imposible" << endl;
	else
		cout << solucion << endl;
	return true;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	while (resuelve());
	//system("PAUSE");
	return 0;
}
