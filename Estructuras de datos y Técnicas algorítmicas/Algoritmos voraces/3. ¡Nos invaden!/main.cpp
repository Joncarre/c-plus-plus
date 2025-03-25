//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool resuelve();
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N*logN), donde N son las ciudades atacadas (es la complejidad de la función 'sort')
bool resuelve(){
	int ciudades, victorias = 0, soldadosEnemigos, soldadosDefensa;
	if (!(cin >> ciudades))
		return false;
	vector<int> enemigos(ciudades);
	vector<int> defensa(ciudades);

	for (int i = 0; i < ciudades; i++){
		cin >> soldadosEnemigos;
		enemigos[i] = soldadosEnemigos;
	}
	for (int i = 0; i < ciudades; i++){
		cin >> soldadosDefensa;
		defensa[i] = soldadosDefensa;
	}
	// Ordenamos ambos vectores de menor a mayor
	sort(enemigos.begin(), enemigos.end());
	sort(defensa.begin(), defensa.end());
	
	// La idea es ir comprobando la defensa con el ataque pero, si la defensa no es suficiente, se incrementará (y el ataque permanecerá igual)
	int indiceE = 0, indiceD = 0; // Establecemos los índices de ambos vectores al principio
	while (indiceD < ciudades){ // Mientras no se llegue al final del vector de defensores...
		if (enemigos[indiceE] <= defensa[indiceD]){
			indiceE++;
			indiceD++;
			victorias++;
		}
		else
			indiceD++;
	}
	cout << victorias << endl;
	return true;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	while (resuelve());
	//system("PAUSE");
	return 0;
}
