//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "MultaMatic.h"
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
	Aplicacion aplicacion;
	string opcion;
	string idTramo;
	int instante;
	string matricula;
	for (int i = 0; i < num; i++){
		cin >> opcion;
		//---------------------------------------------------------------------------------------------------------------------------------------------
		if (opcion == "insertaTramo"){
			cin >> idTramo;
			try{
				aplicacion.insertaTramo(idTramo);
			}
			catch (string error){
				cout << error << endl;
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		else if (opcion == "fotoEntrada"){
			cin >> idTramo; cin >> matricula; instante = time(0);
			try{
				aplicacion.fotoEntrada(idTramo, matricula, instante);
			}
			catch (string error){
				cout << error << endl;
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		else if (opcion == "fotoSalida"){
			cin >> idTramo; cin >> matricula; instante = time(0);
			try{
				aplicacion.fotoSalida(idTramo, matricula, instante);
			}
			catch (string error){
				cout << error << endl;
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		else if (opcion == "multasPorMatricula"){
			cin >> matricula;
			try{
				int numMultas = aplicacion.multasPorMatricula(matricula);
				cout << "La matricula " << matricula << " tiene " << numMultas << " multa(s) en total." << endl;
			}
			catch (string error){
				cout << error << endl;
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		else if (opcion == "multasPorTramos"){
			cin >> idTramo;
			try{
				HashMap<string, int> HashMultaTramo = aplicacion.multasPorTramos(idTramo);
				HashMap<string, int>::ConstIterator it = HashMultaTramo.cbegin();
				while (it != HashMultaTramo.cend()){ // We will iterate through all license plates with fines in the section 'idTramo'
					for (int i = 0; i < it.value(); i++){ // And we will display the license plate as many times as fines it has in this section
						cout << it.key() << endl;
					}
					it.next(); // Move to the next license plate
				}
			}
			catch (string error){
				cout << error << endl;
			}
		}
	}
}
