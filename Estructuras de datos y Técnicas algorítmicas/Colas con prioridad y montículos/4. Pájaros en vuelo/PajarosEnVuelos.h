//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "PriorityQueue.h"

class PajarosEnVuelos
{
private:
	PriorityQueue<int, std :: less_equal<int>> colaMinimos;   // cola de prioridad de minimos que almacenara los valores mayores que el jefe
	PriorityQueue<int,std ::  greater_equal<int>> colaMaximos;  // cola de prioridad de maximos que almacenara los valores menores que el jefe
	int Lider;
	bool son_Mayores_que_Lider(int a, int b);
	bool son_Menores_que_Lider(int a, int b);
	
public:
	PajarosEnVuelos(int lider): Lider(lider) {};
	void insertarPareja(int a, int b);
	int edadLider();
};

