//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#ifndef LISTAPARTIDAS_H
#define LISTAPARTIDAS_H

#include <string>
#include <iostream>
#include "partida.h"
#include "Conecta4.h"
using namespace std;

const int DIM_partida = 5;
typedef tPartida tArray_partida[DIM_partida];

typedef struct{
	tArray_partida lista;
	int cont;
}tListaPartidas;

void guardar(tListaPartidas const &partidas, ofstream &archivo); // Guarda la lista de partidas en el flujo 'archivo'.
bool cargar(tListaPartidas &partidas, ifstream &archivo); // Carga la lista de partidas desde el flujo 'archivo'.
bool insertar(tListaPartidas &partidas, tPartida const &partida); // Dada una partida, si hay espacio en la lista, la añade al final de la lista.

#endif  // LISTAPARTIDAS_H
