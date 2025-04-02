//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include "PriorityQueue.h"
using namespace std;

void resuelve(int elementos);
PriorityQueue<long long> leerCola(int elementos);
long long calculo(PriorityQueue<long long> cola);
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N*logN), donde N es el número de elementos leídos por la entrada
PriorityQueue<long long> leerCola(int elementos){
	PriorityQueue<long long> cola;
	long long numero;
	for (int i = 0; i < elementos; i++){
		cin >> numero;
		cola.push(numero);
	}
	return cola;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N*logN), donde N es el número de elementos que tiene la cola
long long calculo(PriorityQueue<long long> cola){
	long long sumando1 = 0, sumando2 = 0, suma = 0, costeTotal = 0;

	if (cola.size() > 1){
		while (cola.size() > 1){
			sumando1 = cola.top();
			cola.pop();
			sumando2 = cola.top();
			cola.pop();

			suma = sumando1 + sumando2; // El resultado de la suma lo volvemos a meter en la cola
			costeTotal += suma; // El coste total lo vamos acumulando
			cola.push(suma);
		}
		return costeTotal;
	} else
		return 0;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N*logN), es la mayor complejidad que manejan las funciones a las que llama
void resuelve(int elementos){
	PriorityQueue<long long> cola;
	cola = leerCola(elementos);

	long long resultado = calculo(cola);
	cout << resultado << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int elementos;
	cin >> elementos;

	while (elementos > 0){
		resuelve(elementos);
		cin >> elementos;
	}
	//system("PAUSE");
	return 0;
}
