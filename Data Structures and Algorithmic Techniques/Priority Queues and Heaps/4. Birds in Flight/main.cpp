//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include "PriorityQueue.h"
#include "PajarosEnVuelos.h"
using namespace std;

void resuelve(int edad, int parejas);
// ------------------------------------------------------------------------------------------------------
// Complexity: O(1)
int PajarosEnVuelos::edadLider(){
	return Lider;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(1)
bool PajarosEnVuelos::son_Mayores_que_Lider(int a, int b){
	return (a > Lider && b > Lider);
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(1)
bool PajarosEnVuelos::son_Menores_que_Lider(int a, int b){
	return (a < Lider && b < Lider);
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(log N)
void PajarosEnVuelos::insertarPareja(int a, int b){
	if (son_Menores_que_Lider(a, b)){
		colaMaximos.push(a);
		colaMaximos.push(b);
		
		colaMinimos.push(Lider);
		colaMaximos.pop(Lider);
	}
	else if (son_Mayores_que_Lider(a, b)) {
		colaMinimos.push(a);
		colaMinimos.push(b);
		
		colaMaximos.push(Lider);
		colaMinimos.pop(Lider);
	}
	else if (a < Lider && b > Lider) {
		colaMaximos.push(a);
		colaMinimos.push(b);
	}
	else if (a > Lider && b < Lider) {
		colaMinimos.push(a);
		colaMaximos.push(b);
	}
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N log N)
void resuelve(int lider, int parejas){
	int ave1, ave2;
	PajarosEnVuelos app(lider);

	for (int i = 0; i < parejas; i++){
		cin >> ave1; cin >> ave2;
		app.insertarPareja(ave1, ave2);
		cout << app.edadLider();

		if (i < parejas - 1)
			cout << " ";
	}
	cout << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int lider, parejas;
	cin >> lider; cin >> parejas;
	while (!(lider == 0 && parejas == 0)){
		resuelve(lider, parejas);
		cin >> lider; cin >> parejas;
	}
	//system("PAUSE");
	return 0;
}
