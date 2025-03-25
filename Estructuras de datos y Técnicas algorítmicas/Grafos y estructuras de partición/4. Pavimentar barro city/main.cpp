//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <limits>
#include "GrafoValorado.h"
#include "IndexPQ.h"
#include "Pavimentar_City.h"
using namespace std;
// -----------------------------
// Recorrido BFS usando Prim
// -----------------------------
bool resuelve();
GrafoValorado<double> leerGrafo(size_t V);
// ------------------------------------------------------------------------------------------------------
// Complejidad: O()
Pavimentar_City::Pavimentar_City(const GrafoValorado<double> grafo) :
weight(1), marked(grafo.V(), false), distTo(grafo.V(), numeric_limits<double>::infinity()), edgeTo(grafo.V()), pq(grafo.V()), V(grafo.V()), count(0), coste_min(0){
	distTo[0] = 0.0;
	pq.push(1, 0);

	while (!pq.empty()){ // Mientras la cola no esté vacía (o sea, no haya finalizado el BFS)
		int minPQ;
		minPQ = pq.top().elem; // Saco de la cola el vértice siguiente 
		pq.pop();
		visit(grafo, minPQ);
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el número de elementos en el array distTo
int Pavimentar_City::coste_minimo(){
	for (size_t i = 0; i < distTo.size(); i++) // Recorremos todo el array de distancias
	{
		if (distTo[i] != numeric_limits<double>::infinity())
			coste_min += distTo[i]; // Y sumamos el valor de las aristas
	}
	return coste_min;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
bool Pavimentar_City::imposible(){
	return (count <= V - 2); // Obvio, con N - 2 vértices conexos no puedes cubrir N vértices
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O()
void Pavimentar_City::visit(const GrafoValorado<double>  &grafo, int v){
	marked[v] = true;
	count++;

	for (Arista<double> arista : grafo.adj(v)){
		int w = arista.otro(v); // Dame algún vértice adyacente a 'v'
		if (marked[w]) continue; // Si ha sido marcado, no nos molestamos y continuamos con el for (ignorando el resto de código). 
		if (arista.valor() < distTo[w]){ // Si no, comprobamos si el valor para llegar de 'v' a 'w' es menor que la distancia a 'w'
			edgeTo[w] = arista; // Actualizamos la nueva arista
			distTo[w] = arista.valor(); // Acutalizamos el nuevo valor
			// Actualizamos el valor que conlleva ir al vértice 'w'. ¿Por qué no hacer un 'push?
			// Porque no queremos meter un elemento en la pila, sólo queremos actualizar el valor
			// del elemento 'w' (que ya estaba, pues al empezar Prim la cola ya tiene tamaño N).
			pq.update(w, distTo[w]);
		}
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(E + V)
GrafoValorado<double> leerGrafo(size_t V){
	size_t E, v, w, valor;
	GrafoValorado<double> grafo(V);

	cin >> E;
	for (int i = 0; i < E; i++){
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

	Pavimentar_City app(grafo);

	if (app.imposible())
		cout << "Imposible" << endl;
	else
		cout << app.coste_minimo() << endl;
	return true;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	while (resuelve());
	system("PAUSE");
	return 0;
}
