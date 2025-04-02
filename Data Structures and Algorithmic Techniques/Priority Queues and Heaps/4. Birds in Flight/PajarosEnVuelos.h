//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "PriorityQueue.h"

class PajarosEnVuelos  // BirdsInFlight
{
private:
	PriorityQueue<int, std :: less_equal<int>> colaMinimos;   // min priority queue that will store values greater than the leader
	PriorityQueue<int,std ::  greater_equal<int>> colaMaximos;  // max priority queue that will store values less than the leader
	int Lider;  // Leader
	bool son_Mayores_que_Lider(int a, int b);  // are_Greater_than_Leader
	bool son_Menores_que_Lider(int a, int b);  // are_Less_than_Leader
	
public:
	PajarosEnVuelos(int lider): Lider(lider) {};
	void insertarPareja(int a, int b);  // insertPair
	int edadLider();  // leaderAge
};

