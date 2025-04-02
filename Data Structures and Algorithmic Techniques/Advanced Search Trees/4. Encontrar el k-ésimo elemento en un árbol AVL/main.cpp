//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include "Exceptions.h"
#include "TreeMap_Modificado.h"
using namespace std;

void resuelve(int numElementos);
TreeMap_Modificado<int, int> leerArbol(int numElementos);
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N*LogN), donde N es el número de elementos leídos por la entrada
TreeMap_Modificado<int, int> leerArbol(int numElementos){
	TreeMap_Modificado<int, int> arbol;
	int elem;
	for (int i = 0; i < numElementos; i++){
		cin >> elem;
		arbol.insert(elem, 0);
	}
	return arbol;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N*logN), donde N es el número de elementos del árbol (los leídos por la entrada)
void resuelve(int numElementos){
	TreeMap_Modificado<int, int> arbol;
	arbol = leerArbol(numElementos);

	int M, elemento_k;
	cin >> M;
	for (int i = 0; i < M; i++){
		cin >> elemento_k;
		try{
			cout << arbol.k_esimo(elemento_k) << endl;
		}
		catch (NotExistException){
			cout << "??" << endl;
		}
	}
	cout << "----" << endl;
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


