//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

//BIBLIOTECAS
#include <iostream>
#include <cstdlib>
#include <string> 
#include <fstream>
#include <ctime>
#include <ctype.h>
#include <Windows.h>
using namespace std;

// CONSTANTES
const int DIM = 6;
const string FICHERO = "inicializacion1.txt";
const UINT8 NUM_DIRS = 4;
const string NOMB_DIRS[NUM_DIRS] = { "Arriba", "Derecha", "Abajo", "Izquierda" };
const int incF[NUM_DIRS] = {-1, 0, 1, 0 };
const int incC[NUM_DIRS] = { 0, 1, 0,-1 };

// ENUMERADOS
typedef enum tCelda { NULA = 0, VACIA = 2, FICHA = 10 };
typedef enum tEstado{ BLOQUEO, GANA, JUGANDO };

// MATRICES y ARRAYS
typedef tCelda tMat[DIM][DIM];
typedef bool tPosibles[NUM_DIRS]; // Si una posición es 'true' indica que se puede realizar un movimiento en esa dirección

// REGISTROS
typedef struct{
	tMat matriz; // Tablero del juego
	int metaF; // Fila de la casilla meta
	int metaC; // Columna de la casilla meta
	int bolasIniciales;
	int numMovimientos;
	tEstado estado;
}tSoloPeg;

typedef struct{
	tMat matriz; // Tablero del juego
	int metaF; // Fila de la casilla meta
	int metaC; // Columna de la casilla meta
	int bolasIniciales;
	int numMovimientos;
	tEstado estado;
}toloPeg;

typedef struct{
	int col;
	int fil;
	int dir;
}tMovimiento;

//PROTOTIPOS
void mostrar(tSoloPeg const& peg); // Muestra el número de movimientos realizados y el tablero.
bool cargar(tSoloPeg &/*sal*/ peg, string const& nombre); // Carga, desde el archivo 'nombre.txt', el juego completo. Si no es posible, devuelve false.
void guardar(tSoloPeg const& peg, string const& nombre); // Guarda en el fichero 'nombre.txt' el juego que recibe como parámetro.
tCelda intToCelda(int valor); // Recibe un tipo 'int' y devuelve un tipo 'tCelda'.
int celdaToInt(tCelda valor); // Recibe un tipo 'tCelda' y devuelve un tipo 'int'.
void colorFondo(int color); // Función de la biblioteca Windows.h para ajustar colores de fondo.
bool posiblesMovimientos(tSoloPeg const& peg, tMovimiento mov, tPosibles/*sal*/ posibles); // Dada una casilla, marca en posibles las direcciones en las que se podría mover.
bool ejecutarMovimiento(tSoloPeg &/*ent/sal*/ peg, tMovimiento const& mov);	// Dado un movimiento, éste se realiza según las reglas del juego.
bool existeMovimiento(tSoloPeg const& peg); // Comprueba si existe algún movimiento en todo el tablero.
bool direccionValida(tSoloPeg const& peg, tMovimiento mov, int direccion); // Comprueba si una ficha se puede mover en la dirección 'dir'
void salvarPartida(tSoloPeg const& peg); // Da la opción de salvar partida si se introduce un 0.
bool seleccionarDireccion(tMovimiento &/*sal*/ mov, tPosibles &/*sal*/ posibles); // Permite seleccionar la dirección para moverse o 0 para cambiar de ficha.
bool repetirJuego(); // Nos pregunta si queremos volver a jugar.
int menu(); // Muestra un menú para elegir cómo nicializar el tablero.
void generarTablero(tSoloPeg &/*sal*/ peg, int numBolas); // Se intenta generar un tablero con el número de bolas dado.
bool movimientoInverso(tSoloPeg &/*ent/sal*/ peg, tMovimiento &/*ent/sal*/  mov); // Intenta realizar un movimiento inverso seleccionando una ficha.
bool posiblesMovsInv(tSoloPeg const& peg, tMovimiento mov, tPosibles /*sal*/ posibles); // Dada una casilla, marca 'posibles' direcciones en las que podría moverse.
void ejecutarMovInv(tSoloPeg &/*ent/sal*/ peg, tMovimiento &/*ent/sal*/ mov); // Dado un movimiento se realiza el movimiento inverso.
bool direccionValidaInv(tSoloPeg const& peg, tMovimiento mov, int dir); // Comprueba si una ficha se puede mover en 'dir'.
bool existeMovimientoInv(tSoloPeg const& peg); // Comprueba si existe algún movimiento en todo el tablero.
void inicializarTableroInv(tSoloPeg &/*sal*/ peg, int numBolas); // Inicializar (pone las casillas a 'NULA' y establece la meta) el tablero.
void guardarTableroInv(tSoloPeg const& peg); // Da la opción de guardar, en un fichero, el tablero inverso que se ha generado.
