//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#pragma once
#include "PriorityQueue.h"
#include <string>

typedef struct {
	int gravedad;   // severity
	int orden;      // order
	 std :: string nombre;  // name
}tPaciente;


class ColaUrgencias {  // EmergencyQueue
private:

	PriorityQueue<tPaciente, std :: greater_equal<tPaciente>> elementos;
	tPaciente paciente;
	
public:

	/** Constructor:  */
	ColaUrgencias(int t = TAM_INICIAL) : elementos(t)  { paciente.orden = 0; };
	void insertar(std::string nombre, int gravedad);  // insert
	bool esVacia() const;  // isEmpty
	std::string nombrePrimero() const;  // firstPatientName
	void quitarPrimero();  // removeFirst
};


