//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "Faltas.h"
using namespace std;

void ejecutar(int num);

int main(){
	int num;
	while (cin >> num)
		ejecutar(num);
	system("PAUSE");
	return 0;
}

void ejecutar(int num){
	Faltas app;
	string opcion;
	idAsignatura idasignatura;
	idAlumno idalumno;
	numFaltas faltas;
	for (int i = 0; i < num; i++){
		cin >> opcion;
		//-------------------------------------------------------------------------------------------------------------
		if (opcion == "anadirAlumno"){
			cin >> idalumno;
		}
		//-------------------------------------------------------------------------------------------------------------
		else if (opcion == "anadirFalta"){
			cin >> idalumno; cin >> idasignatura;
		}
		//-------------------------------------------------------------------------------------------------------------
		else if (opcion == "anadirAsignatura"){
			cin >> idasignatura;
		}
		//-------------------------------------------------------------------------------------------------------------
		else if (opcion == "noFaltas"){
		}
		//-------------------------------------------------------------------------------------------------------------
		else if (opcion == "totalFaltas"){
			cin >> idalumno;
		}
		//-------------------------------------------------------------------------------------------------------------
		else if (opcion == "maxFaltas"){

		}
	}
}
