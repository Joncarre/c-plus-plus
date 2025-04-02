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
// Complexity: O(N*logN), where N is the number of elements read from input
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
// Complexity: O(N*logN), where N is the number of elements in the queue
long long calculo(PriorityQueue<long long> cola){
	long long sumando1 = 0, sumando2 = 0, suma = 0, costeTotal = 0;

	if (cola.size() > 1){
		while (cola.size() > 1){
			sumando1 = cola.top();
			cola.pop();
			sumando2 = cola.top();
			cola.pop();

			suma = sumando1 + sumando2; // The result of the sum is put back into the queue
			costeTotal += suma; // The total cost is accumulated
			cola.push(suma);
		}
		return costeTotal;
	} else
		return 0;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N*logN), which is the highest complexity of the functions it calls
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
