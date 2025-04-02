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
// Complejidad: O(N), donde N es el número de caracteres leídos por la entrada
Arbin<char> leerArbol(){
	char raiz;
	cin >> raiz;

	if (raiz == '.')
		return Arbin<char>(); // Creamos un nodo vacío
	else{
		// Si no es vacío, entonces los siguientes nodos hijos dependerán de las llamadas recursivas
		const Arbin<char> &iz = leerArbol();
		const Arbin<char> &dr = leerArbol();
		return Arbin<char>(iz, raiz, dr); // Cuando hayan terminado las llamadas a todos los hijos, devolvemos cada nodo construido
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O()
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
// Complejidad: O(N), donde N es el número de nodos del árbol
int altura(Arbin<char> arbol){
	if (arbol.esVacio())
		return 0;
	else
		return 1 + max(altura(arbol.hijoIz()), altura(arbol.hijoDr()));
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(), depende de la complejidad de 'equilibrado()'
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

