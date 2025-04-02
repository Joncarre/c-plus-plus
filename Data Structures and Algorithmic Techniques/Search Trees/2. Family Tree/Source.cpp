//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "Arbin.h"
using namespace std;

void resuelve();
Arbin<int> leerArbol();
bool genealogico(Arbin<int> &arbol, int &padre, int &generaciones);
bool condicion(int hijo, int padre);
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el número de elementos leídos por la entrada
Arbin<int> leerArbol(){
	int numero;
	cin >> numero;

	if (numero == -1)
		return Arbin<int>();
	else{
		const Arbin<int> &iz = leerArbol();
		const Arbin<int> &dr = leerArbol();
		return Arbin<int>(iz, numero, dr);
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el número de nodos
int altura(Arbin<int> &arbol){
	if (arbol.esVacio())
		return 0;
	else
		return 1 + max(altura(arbol.hijoIz()), altura(arbol.hijoDr()));
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
bool condicion(int hijo, int padre){
	if (padre - 18 >= hijo)
		return true;
	else
		return false;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el número de nodos
bool genealogico(Arbin<int> &arbol){
	if (arbol.esVacio()) // Si es vacío...
		return true;
	else if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio()) // Si es hoja...
		return true;
	else if (arbol.hijoDr().esVacio()) // Si no tiene hijo derecho...
		return condicion(arbol.hijoIz().raiz(), arbol.raiz());
	else{ // Si tiene los dos hijos...
		return (genealogico(arbol.hijoIz()) &&
			genealogico(arbol.hijoDr()) &&
			condicion(arbol.hijoIz().raiz(), arbol.raiz()) &&
			condicion(arbol.hijoDr().raiz(), arbol.raiz()) &&
			(arbol.hijoIz().raiz() - 2 >= arbol.hijoDr().raiz()));
	}
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el número de nodos
void resuelve(){
	Arbin<int> arbol;
	arbol = leerArbol();
	bool correcto = genealogico(arbol);
	if (correcto)
		cout << "SI " << altura(arbol) << endl;
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
