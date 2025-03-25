//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <math.h>
#include <stdio.h>
#include "PriorityQueue.h"
using namespace std;

bool resuelve();
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of elements in the input (skiers and skis)
bool resuelve(){
	PriorityQueue<int> altura;
	PriorityQueue<int> longitud;
	int entrada, alt, lon, diferencias = 0;

	cin >> entrada;
	if (entrada == 0)
		return false;

	for (size_t i = 0; i < entrada; i++){ // Fill the height queue
		cin >> alt;
		altura.push(alt);
	}
	for (size_t i = 0; i < entrada; i++){ // Fill the length queue
		cin >> lon;
		longitud.push(lon);
	}
	for (size_t i = 0; i < entrada; i++){
		// We accumulate the difference between heights and lengths (by priority)
		diferencias = diferencias + abs(longitud.top() - altura.top());
		longitud.pop();
		altura.pop();
	}
	cout << diferencias << endl;
	return true;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	while (resuelve());
	//system("PAUSE");
	return 0;
}
