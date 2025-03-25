//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include "SoloPeg.h"
#include <iostream>

bool partida(tSoloPeg &/*ent/sal*/ peg); // Dado un juego inicializado, guía el desarrollo de una partida.
bool leerMovimiento(tSoloPeg const& peg, tMovimiento &/*sal*/ mov); // Lee un movimiento válido y lo devuelve.

int main(){

	tSoloPeg peg;
	string nombreFichero = "inicializacion3.txt";
	bool salir = false;
	int eleccion;

	int op = menu();
	switch (op)
	{
		case 1:
			if (cargar(peg, nombreFichero)) {
				do {
					partida(peg);
					if (repetirJuego()){
						cout << "Introduzca el fichero para cargar el nuevo tablero: " << endl;
						cin >> nombreFichero;
					}
					else
						salir = true;
				} while (!salir);
			}
		break;
		case 2:
			generarTablero(peg, 10);
			// Cuando se salva una partida, creo que la casilla de meta no la marca bien (o sea que las coordenadas que pone en el fichero no son correctas)
			salvarPartida(peg);
		break;
	}

	system("PAUSE");
	return 0;
}

int menu(){
	int opcion;
	do {
		cout << "Elige una opcion: " << endl;
		cout << "1) Generar tablero desde fichero" << endl;
		cout << "2) Generar tablero aleatoriamente " << endl;
		cout << "Opcion: ";
		cin >> opcion;
		if ((opcion < 1) || (opcion > 2)) {
			cout << "Opcion no valida!" << endl;
		}
	} while ((opcion < 1) || (opcion > 2));

	return opcion;
}

bool partida(tSoloPeg &/*ent/sal*/ peg){
	tMovimiento mov;
	bool seguir = false;
	peg.estado = JUGANDO;

	mostrar(peg);

	do {
		if (leerMovimiento(peg, mov)){
			ejecutarMovimiento(peg, mov);
			mostrar(peg);
			seguir = true;
		}
	} while (peg.estado == JUGANDO && seguir);

	if (peg.estado == GANA){
		cout << "Has ganado!!" << endl;
	}
	else if (peg.estado == BLOQUEO){
		cout << "Juego bloqueado!!" << endl;
	}

	return seguir;
}

bool leerMovimiento(tSoloPeg const& peg, tMovimiento &/*sal*/ mov){
	bool repetirEleccion = false;
	bool continuar = true;
	tPosibles posibles;

	do {
		cout << endl << "FICHA (fila y columna) o 0 para salir: ";
		cin >> mov.fil;
		if (mov.fil == 0){ // Si introduce un 0, salvamos la partida y salimos
			salvarPartida(peg);
			continuar = false;
		}
		else {
			cin >> mov.col;	// Si no metió un 0, leemos la columna
			mov.fil = mov.fil - 1;
			mov.col = mov.col - 1;

			if (!((mov.fil < DIM && mov.fil >= 0) && (mov.col < DIM && mov.col >= 0))){ // Si NO está dentro de los límites del tablero...
				cout << "La casilla debe estar dentro de los limites del tablero." << endl;
				repetirEleccion = true;
			}
			else if (!(peg.matriz[mov.fil][mov.col] == FICHA)){ // Si la casilla NO es de tipo 'FICHA'...
				cout << "La casilla debe ser de tipo 'FICHA'" << endl;
				repetirEleccion = true;
			}
			else if (!(posiblesMovimientos(peg, mov, posibles))){	// Si la ficha NO puede realizar movimientos...
				cout << "La casilla debe poder realizar, al menos, un movimiento." << endl;
				repetirEleccion = true;
			}
			else if (!seleccionarDireccion(mov, posibles)){
				repetirEleccion = true;
			}
			else
				repetirEleccion = false;
		}
	} while (repetirEleccion && continuar);

	return continuar;
}
