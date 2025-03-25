//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct{
	int inicio;
	int final;
}tPeli;

void resuelve(int numPelis);
// ------------------------------------------------------------------------------------------------------
// Complexity: O(1)
bool operator <(tPeli a, tPeli b){
	return a.inicio < b.inicio;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of movies (we need to traverse the entire vector)
void resuelve(int numPelis){
	int hora, min, duracion, termina, maxVisualizadas = 1;
	char c;

	vector<tPeli> peliculas(numPelis);
	for (int i = 0; i < numPelis; i++){
		cin >> hora; cin >> c; cin >> min; cin >> duracion;
		peliculas[i].inicio = (hora * 60) + min; // Set the start time of the i-th movie
		peliculas[i].final = (hora * 60) + min + duracion+ 10; // Set the end time of the i-th movie
	}
	sort(peliculas.begin(), peliculas.end(), less<tPeli>()); // Sort the vector from lowest to highest
	int j = 1;
	termina = peliculas[0].final;
	while (j < numPelis){
		if (peliculas[j].inicio >= termina){ // If the start of movie n is greater than or equal to when movie n-1 ends
			termina = peliculas[j].final;
			maxVisualizadas++;
		}
		else if (termina > peliculas[j].final){
			termina = peliculas[j].final; // Update when movie n-1 ends
		}
		j++;
	}
	cout << maxVisualizadas << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int numPelis;
	cin >> numPelis;
	while (numPelis > 0){
		resuelve(numPelis);
		cin >> numPelis;
	}
	//system("PAUSE");
	return 0;
}
