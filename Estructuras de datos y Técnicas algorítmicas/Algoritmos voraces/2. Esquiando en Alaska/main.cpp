//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <math.h>
#include <stdio.h>
#include "PriorityQueue.h"
using namespace std;

bool resuelve();
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el número de elementos en la entrada (esquidadores y esquís)
bool resuelve(){
	PriorityQueue<int> altura;
	PriorityQueue<int> longitud;
	int entrada, alt, lon, diferencias = 0;

	cin >> entrada;
	if (entrada == 0)
		return false;

	for (size_t i = 0; i < entrada; i++){ // Llenamos la cola de alturas
		cin >> alt;
		altura.push(alt);
	}
	for (size_t i = 0; i < entrada; i++){ // Llenamos la cola de longitudes
		cin >> lon;
		longitud.push(lon);
	}
	for (size_t i = 0; i < entrada; i++){
		// Vamos acumulando la diferencia entre alturas y longitudes (por prioridades)
		diferencias = diferencias + abs(longitud.top() - altura.top());
		longitud.pop();
		altura.pop();
	}
	cout << diferencias << endl;
	return true;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	while (resuelve());
	//system("PAUSE");
	return 0;
}
