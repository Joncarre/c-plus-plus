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
// Complexity: O(N logN), where N is the number of batteries in each case
void resuelve(){
	int numCasos, voltaje, numPilas, pila, funcionando, comienzo, final;

		funcionando = 0;
		cin >> numPilas;
		cin >> voltaje;
		vector<int> vectorPilas(numPilas);
		for (int i = 0; i < numPilas; i++){
			cin >> pila;
			vectorPilas[i] = pila; // Put all batteries in the vector
		}
		sort(vectorPilas.begin(), vectorPilas.end()); // Sort the vector from lowest to highest
		// Initialize the indices that will traverse the vector
		comienzo = 0;
		final = numPilas - 1;
		// The idea is to pair the battery with the highest voltage with the one with the lowest voltage and, if not sufficient, increase the lower index
		// to get a battery with more voltage than the previous one
		while (comienzo < final){ // When the indices cross, the vector traversal is finished
			if (vectorPilas[comienzo] + vectorPilas[final] >= voltaje){ // If the two chosen batteries are sufficient...
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
