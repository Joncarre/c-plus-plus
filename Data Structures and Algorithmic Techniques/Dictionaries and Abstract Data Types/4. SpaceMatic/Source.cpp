//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "EspacioMatic.h"
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
	Espacio app;
	idNave idnave;
	idModulo idmodulo;
	nivel nivel;
	string opcion;
	for (int i = 0; i < num; i++){
		cin >> opcion;
		// ---------------------------------------------------------
		if (opcion == "EspacioMatic"){
			// I don't know what the hell this does
		}
		// ---------------------------------------------------------
		else if (opcion == "nuevaNave"){
			cin >> idnave;
			try {
				app.nuevaNave(idnave);
			}
			catch (string error){
				cout << error << endl;
			}
		}
		// ---------------------------------------------------------
		else if (opcion == "equipaNave"){
			cin >> idnave; cin >> idmodulo; cin >> nivel;
			try {
				app.equipaNave(idnave, idmodulo, nivel);
			}
			catch (string error){
				cout << error << endl;
			}
		}
		// ---------------------------------------------------------
		else if (opcion == "estropeaNave"){
			cin >> idnave; cin >> idmodulo;
			try {
				app.estropeaNave(idnave, idmodulo);
			}
			catch (string error){
				cout << error << endl;
			}
		}
		// ---------------------------------------------------------
		else if (opcion == "navesDefectuosas"){
			try {
				List<idNave> lista = app.navesDefectuosas();
				List<idNave>::Iterator it = lista.begin();
				while (it != lista.end()){
					cout << it.elem() << endl;
					it.next();
				}
			}
			catch (string error){
				cout << error << endl;
			}
		}
		// ---------------------------------------------------------
		else if (opcion == "modulosNave"){
			cin >> idnave;
			try {
				List<idModulo> lista = app.modulosNave(idnave);
				List<idModulo>::ConstIterator it = lista.cbegin();
				while (it != lista.cend()){
					cout << it.elem() << endl;
					it.next();
				}
			}
			catch (string error){
				cout << error << endl;
			}
		}


	}
}
