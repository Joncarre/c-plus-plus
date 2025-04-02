//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"
using namespace std;

typedef struct{
	int inicio;
	int final;
}tConferencia;

void resuelve(int numConferencias);
// ------------------------------------------------------------------------------------------------------
// Complexity: O(1)
bool operator <(tConferencia a, tConferencia b){
	return a.inicio < b.inicio;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N*logN), due to the 'sort' operation
void resuelve(int numConferencias){
	int minSalas = 1;

	vector<tConferencia> lista(numConferencias);
	tConferencia conferencia;

	for (int i = 0; i < numConferencias; i++){
		cin >> conferencia.inicio;
		cin >> conferencia.final;
		lista[i] = conferencia;
	}

	PriorityQueue<int> salasOcupadas;
	sort(lista.begin(), lista.end(), less<tConferencia>());
	salasOcupadas.push(lista[0].final);

	int j = 1;
	while (j < numConferencias){
		if (lista[j].inicio >= salasOcupadas.top())
			salasOcupadas.pop();
		else
			minSalas++;
		salasOcupadas.push(lista[j].final);
		j++;
	}
	cout << minSalas << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int numConferencias;
	cin >> numConferencias;
	while (numConferencias > 0){
		resuelve(numConferencias);
		cin >> numConferencias;
	}
	system("PAUSE");
	return 0;
}
