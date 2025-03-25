//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include "Arbin.h"
using namespace std;
void resuelve();
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es la cantidad de números en la entrada
Arbin<int>* leerArbol(){
	int entrada;
	cin >> entrada;
	if (entrada == -1)
		return new Arbin<int>();
	else{
		Arbin<int> *iz = leerArbol();
		Arbin<int> *dr = leerArbol();
		return new Arbin<int> (*iz, entrada, *dr);
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es la cantidad de números en la entrada
void resuelve(){
	Arbin<int> *arbol = leerArbol();
	if (arbol->equilibradoPublico() && arbol->ordenadoPublico())	// Si es ordenado (de búsqueda) y está equilibrado...
		cout << "SI" << endl;
	else
		cout << "NO" << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; i++){
		resuelve();
	}
	system("PAUSE");
	return 0;
}
