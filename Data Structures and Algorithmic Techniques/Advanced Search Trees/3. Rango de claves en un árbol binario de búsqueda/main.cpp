//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include "BinTree.h"
#include "TreeMap_AVL.h"
#include "TreeMapRango.h"
using namespace std;

void resuelve(int numElementos);
TreeMapRango<int, int> leerArbol(int numElementos);

// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el número de elementos leídos por la entrada
TreeMapRango<int, int> leerArbol(int numElementos){
	TreeMapRango<int, int> arbol;
	int nodo;
	for (int i = 0; i < numElementos; i++){
		cin >> nodo;
		arbol.insert(nodo, 0); // La clave es lo que leemos por la entrada y el valor lo podemos poner a 0
	}
	return arbol;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: max(O(N) + O(log N)), por las funciones 'leerArbol' y 'rango', luego la complejidad es O(N)
void resuelve(int numElementos){
	TreeMapRango<int, int> arbol;
	arbol = leerArbol(numElementos);

	int k1, k2;
	cin >> k1; cin >> k2;

	vector<int> lista;
	lista = arbol.rango(k1, k2); // Obtenemos los elementos dentro del intervalo [k1, k2]

	int N = lista.size();
	
	if (N > 0){
		for (int i = 0; i < N; i++){
			cout << lista.at(i);
			if (i < N - 1)
				cout << " ";
		}
	}
	cout << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int numElementos;
	cin >> numElementos;

	while (numElementos > 0){
		resuelve(numElementos);
		cin >> numElementos;
	}
	//system("PAUSE");
	return 0;
}
