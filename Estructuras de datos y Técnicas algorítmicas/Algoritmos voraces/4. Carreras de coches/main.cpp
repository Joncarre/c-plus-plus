//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"
using namespace std;

void resuelve();
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N logN), donde N es el número de pilas de cada caso
void resuelve(){
	int numCasos, voltaje, numPilas, pila, funcionando, comienzo, final;

		funcionando = 0;
		cin >> numPilas;
		cin >> voltaje;
		vector<int> vectorPilas(numPilas);
		for (int i = 0; i < numPilas; i++){
			cin >> pila;
			vectorPilas[i] = pila; // Metemos todas las pilas en el vector
		}
		sort(vectorPilas.begin(), vectorPilas.end()); // Ordenamos el vector de menor a mayor
		// Inicializamos los índices que van a recorrer el vector
		comienzo = 0;
		final = numPilas - 1;
		// La idea es ir emparejando la pila de mayor voltaje con la de menor voltaje y, si no es suficiente, aumentar el índice menor
		// para coger una pila con más voltaje que la anterior
		while (comienzo < final){ // Cuando los índices se crucen, se terminó el recorrido del vector
			if (vectorPilas[comienzo] + vectorPilas[final] >= voltaje){ // Si las dos pilas escogidas son suficientes...
				comienzo++;
				final--;
				funcionando++;
			}
			else
				comienzo++;
		}
		cout << funcionando << endl;
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
