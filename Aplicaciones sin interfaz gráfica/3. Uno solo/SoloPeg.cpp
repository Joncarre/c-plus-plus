//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include "SoloPeg.h"
#include <iostream>
using namespace std;

void generarTablero(tSoloPeg &/*sal*/ peg, int numBolas){
	srand(time(NULL));
	tMovimiento mov;
	bool seguir = true;

	inicializarTableroInv(peg, 10);
	
	mostrar(peg);

	while (peg.bolasIniciales < numBolas && seguir){
		if (existeMovimientoInv(peg)){
			if (movimientoInverso(peg, mov)){
				ejecutarMovInv(peg, mov);
			}
			else {
				seguir = false;
				cout << "Imposible seguir generando el tablero." << endl;
			}
			mostrar(peg);
		}
	}
}

void ejecutarMovInv(tSoloPeg &/*ent/sal*/ peg, tMovimiento &/*ent/sal*/ mov){ // Pues hay que actualizar la casilla desde la que se realizar el siguiente movimiento inverso
	int vecinaF;
	int vecinaC;

	vecinaF = mov.fil + incF[mov.dir];
	vecinaC = mov.col + incC[mov.dir];

	peg.matriz[vecinaF + incF[mov.dir]][vecinaC + incC[mov.dir]] = FICHA; // En la segunda vecina mete 'FICHA'
	peg.matriz[vecinaF][vecinaC] = FICHA; // En la primera vecina se mete 'FICHA'
	peg.matriz[mov.fil][mov.col] = VACIA; // En la actual se mete 'VACIA'

	peg.bolasIniciales = peg.bolasIniciales++;
}

bool movimientoInverso(tSoloPeg &/*ent/sal*/ peg, tMovimiento &/*ent/sal*/  mov){
	tPosibles posibles;

	int correcto = false;

	while (!correcto){
		// Generamos una casilla dentro de las dimensiones del tablero
		mov.fil = rand() % (DIM);
		mov.col = rand() % (DIM);
		if (peg.matriz[mov.fil][mov.col] == FICHA){ // Si la casilla generada es de tipo 'FICHA'...
			if (posiblesMovsInv(peg, mov, posibles)) { // Si existe, al menos, un movimiento válido desde esa casilla...
				// Generamos una dirección entre [0, 3]
				int dir = rand() % (4);
				while (posibles[dir] == false){	// Seguimos generando hasta que la 'dir' sea una dirección válida
					dir = rand() % (4);
				}
				mov.dir = dir;
				correcto = true;
			}
		}
	}

	return correcto;
}

bool posiblesMovsInv(tSoloPeg const& peg, tMovimiento mov, tPosibles /*sal*/ posibles){
	for (int dir = 0; dir < NUM_DIRS; dir++)
		posibles[dir] = false;

	bool valido = false;

	for (int dir = 0; dir < NUM_DIRS; dir++){
		if (direccionValidaInv(peg, mov, dir)){
			posibles[dir] = true;
			valido = true;
		}
	}
	return valido;
}

bool direccionValidaInv(tSoloPeg const& peg, tMovimiento mov, int dir){
	bool valida = false;
	int vecinaF;
	int vecinaC;

	vecinaF = mov.fil + incF[dir];
	vecinaC = mov.col + incC[dir];

	// Si la segunda vecina está dentro del límite y no es 'FICHA'...
	if (peg.matriz[vecinaF + incF[dir]][vecinaC + incC[dir]] != FICHA &&
		((vecinaF + incF[dir] < DIM && vecinaF + incF[dir] >= 0) &&
		(vecinaC + incC[dir] < DIM && vecinaC + incC[dir] >= 0))){
		// Además, si la primera vecina no es 'FICHA'...
		if (peg.matriz[vecinaF][vecinaC] != FICHA){
			valida = true;
		}
	}
	return valida;
}

bool existeMovimientoInv(tSoloPeg const& peg){
	bool hayMovimientos = false;
	tMovimiento movimientos;
	tPosibles posibles;

	int f = 0;
	int c = 0;
	// NOTA: mejorar esto para que cuando haya encontrado un movimiento posible, no siga ejecuanto el doble While
	while (f < DIM){
		while (c < DIM){
			movimientos.fil = f;
			movimientos.col = c;
			if (peg.matriz[f][c] == FICHA)
				if (posiblesMovsInv(peg, movimientos, posibles))
					hayMovimientos = true;
			c++;
		}
		c = 0;
		f++;
	}
	return hayMovimientos;
}

void inicializarTableroInv(tSoloPeg &/*sal*/ peg, int numBolas){
	for (int fila = 0; fila < DIM; fila++){
		for (int columna = 0; columna < DIM; columna++){
			peg.matriz[fila][columna] = NULA; // Ponemos todas las posiciones a 'NULA'
		}
	}

	// Elegimos la meta de forma aleatoria
	peg.metaF = rand() % (DIM);
	peg.metaC = rand() % (DIM);
	peg.matriz[peg.metaF][peg.metaC] = FICHA;
	// Establecemos el número de bolas que tendrá el tablero generado y los movimientos
	peg.bolasIniciales = numBolas;
	peg.numMovimientos = 0;
}

void guardarTableroInv(tSoloPeg const& peg){
 	// ...
}

bool existeMovimiento(tSoloPeg const& peg){
	bool hayMovimientos = false;
	tMovimiento movimientos;
	tPosibles posibles;

	int f = 0;
	int c = 0;

	while (f < DIM){
		while (c < DIM){
			movimientos.fil = f;
			movimientos.col = c;
			if (peg.matriz[f][c] == FICHA)
				if (posiblesMovimientos(peg, movimientos, posibles))
					hayMovimientos = true;
			c++;
		}
		c = 0;
		f++;
	}
	return hayMovimientos;
}

bool ejecutarMovimiento(tSoloPeg &/*ent/sal*/ peg, tMovimiento const& mov){
	bool correcto = true;
	int vecinaF;
	int vecinaC;

	vecinaF = mov.fil + incF[mov.dir];
	vecinaC = mov.col + incC[mov.dir];

	peg.matriz[vecinaF + incF[mov.dir]][vecinaC + incC[mov.dir]] = FICHA; // En la segunda vecina mete 'FICHA'
	peg.matriz[vecinaF][vecinaC] = VACIA; // En la primera vecina se mete 'VACIA'
	peg.matriz[mov.fil][mov.col] = VACIA; // En la actual se mete 'VACIA'

	peg.numMovimientos++;
	peg.bolasIniciales = peg.bolasIniciales - peg.numMovimientos;

	// Si sólo queda una bola y ésta está en la celda de meta...
	if (peg.bolasIniciales == 1 && peg.matriz[vecinaF + incF[mov.dir]][vecinaC + incC[mov.dir]] == peg.matriz[peg.metaF - 1][peg.metaC - 1]){
		peg.estado = GANA;
	}
	else if (!existeMovimiento(peg)){
		peg.estado = BLOQUEO;
	}
	else {
		peg.estado = JUGANDO;
	}
	return correcto;
}

bool posiblesMovimientos(tSoloPeg const& peg, tMovimiento mov, tPosibles/*sal*/ posibles){
	/*
	* Es necesario que cada vez que comprobemos los movimientos, pongamos las direcciones del array 'posibles' a false.
	* Si no hacemos esto podría pasar lo siguiente: llamamos a una casilla que puede mover solo 'arriba'. Después llamamos a otra
	* que puede mover 'arriba' y 'abajo'. Y si volvemos a llamar a la primera, en vez de decirnos que sólo puede mover 'arriba', nos dirá
	* que puede mover 'arriba' y 'abajo', lo cual no es cierto.
	*/
	for (int dir = 0; dir < NUM_DIRS; dir++)
		posibles[dir] = false;

	bool valido = false;

	for (int dir = 0; dir < NUM_DIRS; dir++){
		if (direccionValida(peg, mov, dir)){
			posibles[dir] = true;
			valido = true;
		}
	}
	return valido;
}

void mostrar(tSoloPeg const& peg){
	colorFondo(0);
	cout << "Movimientos: " << peg.numMovimientos << endl << endl;
	tCelda valorLeido;

	cout << "  1 2 3 4 5 6" << endl << endl; // Mostramos la primera línea antes de comenzar a recorrer la matriz
	for (int fila = 0; fila < DIM; fila++){
		cout << fila + 1 << " ";
		for (int columna = 0; columna < DIM; columna++){
			valorLeido = peg.matriz[fila][columna]; // Leemos el tCelda de la matriz
			colorFondo(celdaToInt(valorLeido)); // Pasamos el 'valorLeido' a un 'int' y se lo pasamos a la función colorFondo para que lo pinte
			if (fila == peg.metaF && columna == peg.metaC){	/// Si la casilla coincide con la casilla final...
				cout << char(254);
			}
			else{
				cout << " ";
			}
			colorFondo(0);	// Hacemos que pinte un negro antes de pintar cada casilla
			cout << " ";

		}
		cout << endl << endl;
	}
}

bool cargar(tSoloPeg &/*sal*/ peg, string const& nombre){
	bool exito = true;
	ifstream fichero;
	int valorLeido;
	int dimensiones;

	fichero.open(nombre);

	if (!fichero.is_open()){
		cout << "No existe el fichero." << endl;
		exito = false;
	}
	else {
		fichero >> dimensiones; // Primero leemos las dimensiones de fichero
		if (dimensiones != DIM){ // Y si no coinciden con las establecidas, entonces devolvemos 'false'
			cout << "Dimensiones de fichero incorrectas. Introduzca un nuevo fichero: " << endl;
			exito = false;
		}
		else {
			fichero >> peg.bolasIniciales;
			fichero >> peg.metaF;
			fichero >> peg.metaC;
			for (int fila = 0; fila < DIM; fila++){
				for (int columna = 0; columna < DIM; columna++){
					fichero >> valorLeido;
					peg.matriz[fila][columna] = intToCelda(valorLeido);
				}
			}
			fichero >> peg.numMovimientos;
			fichero.close();
		}
	}
	return exito;
}

void guardar(tSoloPeg const& peg, string const& nombre){
	ofstream fichero;
	tCelda valorLeido;

	fichero.open(nombre);

	if (!fichero.is_open())
		cout << "No existe el fichero." << endl;
	else {
		fichero << DIM << endl;
		fichero << peg.bolasIniciales << endl;
		fichero << peg.metaF << endl;
		fichero << peg.metaC << endl;

		for (int fila = 0; fila < DIM; fila++){
			for (int columna = 0; columna < DIM; columna++){
				valorLeido = peg.matriz[fila][columna];
				if (columna == DIM - 1)	// Si hemos llegado a la última columna, no metemos espacio
					fichero << celdaToInt(valorLeido);
				else {
					if (valorLeido < 10)	// Si es un número menor que 10, se meten dos espacios (para que quede bonito el fichero)
						fichero << celdaToInt(valorLeido) << "  ";
					else
						fichero << celdaToInt(valorLeido) << " ";
				}
			}
			fichero << endl;
		}
		fichero << peg.numMovimientos;
	}
}

bool direccionValida(tSoloPeg const& peg, tMovimiento mov, int dir){
	bool valida = false;
	int vecinaF;
	int vecinaC;

	vecinaF = mov.fil + incF[dir];
	vecinaC = mov.col + incC[dir];

	// Si la segunda vecina está dentro del límite y es 'VACIA'...
	if (peg.matriz[vecinaF + incF[dir]][vecinaC + incC[dir]] == VACIA &&
		((vecinaF + incF[dir] < DIM && vecinaF + incF[dir] >= 0) &&
		(vecinaC + incC[dir] < DIM && vecinaC + incC[dir] >= 0))){
		// Además, si la primera vecina es 'FICHA'...
		if (peg.matriz[vecinaF][vecinaC] == FICHA){
			valida = true;
		}
	}
	return valida;
}

void salvarPartida(tSoloPeg const& peg){
	string fichero;
	int salvar;

	do {
		cout << "Desea salvar?" << endl << "1) Si" << endl << "2) No" << endl;
		cin >> salvar;
		if ((salvar < 1) || (salvar > 2)) {
			cout << "Opcion no valida!" << endl;
		}
	} while ((salvar < 1) || (salvar > 2));

	if (salvar == 1){
		cout << "Introduce el nombre del fichero: " << endl;
		cin >> fichero;
		guardar(peg, fichero);
	}
}

bool seleccionarDireccion(tMovimiento &/*sal*/ mov, tPosibles &/*sal*/ posibles){
	bool direccionCorrecta = false;

	cout << "Selecciona una direccion o 0 para cambiar de ficha: " << endl;

	for (int dir = 0; dir < NUM_DIRS; dir++){ // For que muestra las posibles direcciones que podemos elegir
		if (posibles[dir] == true){
			cout << dir + 1 << " - " << NOMB_DIRS[dir] << endl;
		}
	}

	cin >> mov.dir;
	if (mov.dir == 0){
		cout << "Elija una nueva ficha." << endl;
	}
	else {
		do {
			if (posibles[mov.dir - 1] == true){	// Si la dirección elegida es correcta...
				mov.dir = mov.dir - 1;	// Preparamos el movimiento para que lo use la función ejecutaMovimiento()
				direccionCorrecta = true;
			}
			else {
				cout << "Direccion incorrecta." << endl;
				cin >> mov.dir;
			}
		} while (!direccionCorrecta);
	}
	return direccionCorrecta;
}

bool repetirJuego(){
	int jugar;
	do {
		cout << "Desea jugar otra vez?" << endl << "1) Si" << endl << "2) No" << endl;
		cin >> jugar;
		if ((jugar < 1) || (jugar > 2)) {
			cout << "Opcion no valida!" << endl;
		}
	} while ((jugar < 1) || (jugar > 2));

	if (jugar == 1){
		return true;
	}
	else
		return false;
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

tCelda intToCelda(int valor){
	switch (valor){
	case 0:
		return NULA; break;
	case 2:
		return VACIA; break;
	case 10:
		return FICHA; break;
	default:
		break;
	}
}

int celdaToInt(tCelda valor){
	switch (valor){
	case NULA:
		return 0; break;
	case VACIA:
		return 2; break;
	case FICHA:
		return 10; break;
	default:
		break;
	}
}
