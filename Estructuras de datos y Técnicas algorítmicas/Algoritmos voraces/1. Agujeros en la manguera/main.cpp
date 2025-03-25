//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
using namespace std;

bool resuelve();
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el número de agujeros en la manguera
bool resuelve(){
	size_t N, L, agujeroActual, agujeroSiguiente, distancia, longParche, numParches;

	if (!(cin >> N))
		return false;
	cin >> L;
	longParche = L;
	numParches = 1;
	cin >> agujeroActual;
	for (size_t i = 1; i < N; i++){
		cin >> agujeroSiguiente;
		distancia = agujeroSiguiente - agujeroActual;
		if (distancia > longParche){ // Si la distancia a cubrir es mayor que la del parche...
			numParches++; // Hace falta poner otro parche
			longParche = L; // Cuya medida es la propia medida del parche
		}
		else
			longParche = longParche - distancia; // Acortamos el parche y puede que nos sirva para tapar el próximo agujero
		agujeroActual = agujeroSiguiente;
	}
	cout << numParches << endl;
	return true;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	while (resuelve());
	//system("PAUSE");
	return 0;
}
