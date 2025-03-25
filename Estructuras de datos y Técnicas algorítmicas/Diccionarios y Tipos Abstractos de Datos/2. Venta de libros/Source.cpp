//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "VentaLibros.h"
using namespace std;

int main(){
	arrancar();
	return 0;
}

void arrancar(){
	int numCasos;
	string opcion;
	ClaveLibro nombreLibro;
	Aplicacion aplicacion;
	int numEjemplares;

	while (true){
		cin >> numCasos;
		for (int i = 0; i < numCasos; i++){
			cin >> opcion;
			if (opcion == "nuevoLibro"){
				cin >> numEjemplares; cin >> nombreLibro;
				aplicacion.nuevoLibro(nombreLibro, numEjemplares);
			}
			else if (opcion == "comprar"){
				cin >> nombreLibro;
				try{
					aplicacion.comprar(nombreLibro);
				}
				catch (invalid_argument& e){
					cout << e.what() << endl << "---" << endl;
				}
				catch (out_of_range& o){
					cout << o.what() << endl << "---" << endl;
				}
			}
			else if (opcion == "estaLibro"){
				cin >> nombreLibro;
				aplicacion.estaLibro(nombreLibro);
			}
			else if (opcion == "elimLibro"){
				cin >> nombreLibro;
				aplicacion.elimLibro(nombreLibro);
			}
			else if (opcion == "numEjemplares"){
				cin >> nombreLibro;
				try{
					cout << "Existen " << aplicacion.numEjemplares(nombreLibro) << " ejemplares del libro " << nombreLibro << endl;
				}
				catch (invalid_argument& e){
					cout << e.what() << endl << "---" << endl;
				}
			}
			else if (opcion == "top10"){
				aplicacion.mostrar();
			}
		}
	}
}
