//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include "Arbin.h"
using namespace std;

void resuelve();
Arbin<char> leerArbol();
bool equilibrado(Arbin<char> arbol);
int altura(Arbin<char> arbol);

// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of characters read from the input
Arbin<char> leerArbol(){
	char raiz;
	cin >> raiz;

	if (raiz == '.')
		return Arbin<char>(); // Create an empty node
	else{
		// If it's not empty, then the following child nodes will depend on recursive calls
		const Arbin<char> &iz = leerArbol();
		const Arbin<char> &dr = leerArbol();
		return Arbin<char>(iz, raiz, dr); // When the calls to all children have finished, we return each constructed node
	}
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O()
bool equilibrado(Arbin<char> arbol){
	if (arbol.esVacio())
		return true;
	else{
		if (equilibrado(arbol.hijoIz()) &&
			equilibrado(arbol.hijoDr()) &&
			(altura(arbol.hijoIz()) - altura(arbol.hijoDr()) <= 1 &&
			altura(arbol.hijoDr()) - altura(arbol.hijoIz()) <= 1))
			return true;
		else 
			return false;
	}
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of nodes in the tree
int altura(Arbin<char> arbol){
	if (arbol.esVacio())
		return 0;
	else
		return 1 + max(altura(arbol.hijoIz()), altura(arbol.hijoDr()));
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(), depends on the complexity of 'equilibrado()'
void resuelve(){
	Arbin<char> arbol;

	arbol = leerArbol();
	if (equilibrado(arbol))
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
	//system("PAUSE");
	return 0;
}

