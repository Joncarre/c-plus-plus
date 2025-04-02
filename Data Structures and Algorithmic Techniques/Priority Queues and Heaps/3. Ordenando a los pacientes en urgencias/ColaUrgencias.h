//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#pragma once
#include "PriorityQueue.h"
#include <string>

typedef struct {
	int gravedad;
	int orden;
	 std :: string nombre;
}tPaciente;


class ColaUrgencias {
private:

	PriorityQueue<tPaciente, std :: greater_equal<tPaciente>> elementos;
	tPaciente paciente;
	
public:

	/** Constructor:  */
	ColaUrgencias(int t = TAM_INICIAL) : elementos(t)  { paciente.orden = 0; };
	void insertar(std::string nombre, int gravedad);
	bool esVacia() const;
	std::string nombrePrimero() const;
	void quitarPrimero();
};


