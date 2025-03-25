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
// Redefinición de 'operator' para el orden de la cola
bool operator >= (tPaciente a, tPaciente b) {
	if (b.gravedad < a.gravedad) return true;
	else if (a.gravedad == b.gravedad && a.orden < b.orden) return true;
	else return false;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N*logN), donde N es el número de elementos de la cola
void ColaUrgencias::insertar(std::string nombre, int gravedad){
	paciente.nombre = nombre;
	paciente.gravedad = gravedad;
	paciente.orden += 1;
	elementos.push(paciente);
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
bool ColaUrgencias::esVacia() const{
	return elementos.empty();
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
string ColaUrgencias::nombrePrimero() const{
	return elementos.top().nombre;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
void ColaUrgencias::quitarPrimero(){
	elementos.pop();	
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N*logN), por la función 'insertar'
void resuelve(int numCasos){
	ColaUrgencias app;
	char opcion;
	string nombre;
	int gravedad;

	for (int i = 0; i < numCasos; i++){
		cin >> opcion;
		if (opcion == 'A'){ // Si leemos una "A"...
			cout << app.nombrePrimero() << endl;
			app.quitarPrimero();
		}
		else{ // Si leemos una "I"...
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
