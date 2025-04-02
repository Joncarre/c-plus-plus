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
// Complexity: O(N), where N is the number of elements read from the input
TreeMapRango<int, int> leerArbol(int numElementos){
	TreeMapRango<int, int> arbol;
	int nodo;
	for (int i = 0; i < numElementos; i++){
		cin >> nodo;
		arbol.insert(nodo, 0); // The key is what we read from the input and the value can be set to 0
	}
	return arbol;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: max(O(N) + O(log N)), due to the functions 'leerArbol' and 'rango', so the complexity is O(N)
void resuelve(int numElementos){
	TreeMapRango<int, int> arbol;
	arbol = leerArbol(numElementos);

	int k1, k2;
	cin >> k1; cin >> k2;

	vector<int> lista;
	lista = arbol.rango(k1, k2); // Get the elements within the interval [k1, k2]

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
