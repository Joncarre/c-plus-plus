//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
using namespace std;

bool resuelve();
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of holes in the hose
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
		if (distancia > longParche){ // If the distance to cover is greater than the patch length...
			numParches++; // Another patch is needed
			longParche = L; // With a measure equal to the patch length
		}
		else
			longParche = longParche - distancia; // We reduce the patch length and it might be useful for covering the next hole
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
