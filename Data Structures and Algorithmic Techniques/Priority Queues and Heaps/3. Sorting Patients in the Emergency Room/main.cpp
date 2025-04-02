//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include "PriorityQueue.h"
#include "ColaUrgencias.h"
using namespace std;

void resuelve(int numCasos);
// ------------------------------------------------------------------------------------------------------
// Redefinition of 'operator' for queue ordering
bool operator >= (tPaciente a, tPaciente b) {
	if (b.gravedad < a.gravedad) return true;
	else if (a.gravedad == b.gravedad && a.orden < b.orden) return true;
	else return false;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N*logN), where N is the number of elements in the queue
void ColaUrgencias::insertar(std::string nombre, int gravedad){
	paciente.nombre = nombre;
	paciente.gravedad = gravedad;
	paciente.orden += 1;
	elementos.push(paciente);
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(1)
bool ColaUrgencias::esVacia() const{
	return elementos.empty();
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(1)
string ColaUrgencias::nombrePrimero() const{
	return elementos.top().nombre;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(1)
void ColaUrgencias::quitarPrimero(){
	elementos.pop();	
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N*logN), due to the 'insertar' function
void resuelve(int numCasos){
	ColaUrgencias app;
	char opcion;
	string nombre;
	int gravedad;

	for (int i = 0; i < numCasos; i++){
		cin >> opcion;
		if (opcion == 'A'){ // If we read an "A"...
			cout << app.nombrePrimero() << endl;
			app.quitarPrimero();
		}
		else{ // If we read an "I"...
			cin >> nombre;
			cin >> gravedad;
			app.insertar(nombre, gravedad);
		}
	}
	cout << "----" << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int numCasos;
	cin >> numCasos;

	while (numCasos > 0){
		resuelve(numCasos);
		cin >> numCasos;
	}
	system("PAUSE");
	return 0;
}
