//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include "Arbin.h"
using namespace std;

void resuelve();
// -----------------------------------------------------------------
// Complejidad: O(N), donde N es el número de nodos en la entrada
void tiempoAyuda(const Arbin<char> &arbol, int &tiempo){
	if (arbol.esVacio()){ // Si es vacío...
		tiempo = 0;
	}
	else {
		int tiempoIz, tiempoDr;
		// LLAMADA RECURSIVA
		tiempoAyuda(arbol.hijoIz(), tiempoIz);
		tiempoAyuda(arbol.hijoDr(), tiempoDr);
		// CÁLCULO DEL TIEMPO
		tiempo = tiempoIz + tiempoDr;
		if (arbol.raiz() == 'X' && tiempo == 0)
			tiempo++;
		else if (tiempo > 0)
			tiempo++;
	}
}
// -----------------------------------------------------------------
// Complejidad: O(N), donde N es el número de nodos en la entrada
Arbin<char> leerArbol(){
	char entrada;
	cin >> entrada;
	if (entrada == '.')
		return Arbin<char>();
	else{
		const Arbin<char> &iz = leerArbol();
		const Arbin<char> &dr = leerArbol();
		return Arbin<char>(iz, entrada, dr);
	}
}
// -----------------------------------------------------------------
// Complejidad: O(N), donde N es el número de nodos en la entrada
void resuelve(){
	int tiempo = 0;
	Arbin<char> arbol = leerArbol();
	tiempoAyuda(arbol, tiempo);
	// El "tiempo - 1" se pone porque una vez que la recursión ha llegado a la cima, igualmente le suma 1,
	// pero en realidad no debe sumarle nada...
	cout << "Tiempo: " <<  tiempo - 1 << endl;
}
// -----------------------------------------------------------------
int main(){
	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; i++){
		resuelve();
	}
	system("PAUSE");
	return 0;
}
