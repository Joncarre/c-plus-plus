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
// Complexity: O(N*logN), where N is the number of attacked cities (this is the complexity of the 'sort' function)
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
	// Sort both vectors from lowest to highest
	sort(enemigos.begin(), enemigos.end());
	sort(defensa.begin(), defensa.end());
	
	// The idea is to compare defense with attack but, if the defense is not enough, it will increase (and the attack will remain the same)
	int indiceE = 0, indiceD = 0; // Set the indices of both vectors at the beginning
	while (indiceD < ciudades){ // While we haven't reached the end of the defenders vector...
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
