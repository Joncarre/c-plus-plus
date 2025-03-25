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

typedef struct{
	tPartida *lista[DIM_partida];
	int cont;
	int tam;
}tListaPartidas;

// Guarda la lista de partidas en el flujo 'archivo'.
void guardar(tListaPartidas const &partidas, ofstream &archivo);
// Carga la lista de partidas desde el flujo 'archivo'.
bool cargar(tListaPartidas &partidas, ifstream &archivo);
// Dada una partida, si hay espacio en la lista, la añade al final de la lista.
bool insertar(tListaPartidas &partidas, tPartida const &partida);
// Inicializa una lista de partidas de tamaño 'DIM_partida'
void iniciar(tListaPartidas &partidas);
// Redimensiona la lista de partidas.
void redimensionar(tListaPartidas &partidas, int dim);
// Elimina la memoria usada por la lista dinámica de partidas.
void destruir(tListaPartidas &partidas);

#endif  // LISTAPARTIDAS_H
