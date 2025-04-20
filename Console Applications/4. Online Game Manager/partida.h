//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include <iostream>
#include "fecha.h"
#include "Conecta4.h"
using namespace std;

typedef enum { EnCurso, Terminada } tEstadoPartida;

typedef struct {
	string id_Partida;
	string jugador1;
	string jugador2;
	tFecha inicio;
	tFecha actualizacion;
	tEstadoPartida estadoPartida;
	tConecta4 juego;
}tPartida;

void nueva(tPartida & partida, string const& jugador1, string const& jugador2); // Recibe los identificadores de los adversarios (sus nombres) y devuelve una partida con todos sus datos rellenos.
bool aplicarJugada(tPartida & partida, int col); // Aplica la jugada col al juego, y si se pudo realizar, devuelve true y actualiza los demás campos de la partida.
void abandonar(tPartida & partida); // Modifica el estado de la partida a 'Terminada', y la fecha de la última actualización.
void guardar(tPartida const& partida, ofstream & archivo); // Dado un flujo de archivo, escribe los datos de la partida.
bool cargar(tPartida & partida, ifstream & archivo); // Dado un flujo de archivo, lee los datos de la partida.


#endif  // PARTIDA_H
