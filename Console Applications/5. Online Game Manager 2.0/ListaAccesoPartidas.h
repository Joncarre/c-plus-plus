//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#ifndef LISTACCESOPARTIDAS_H
#define LISTACCESOPARTIDAS_H

#include <string>
#include <iostream>
#include "partida.h"
using namespace std;

const int MAX_PAR_US = 3;

typedef struct {
	string identificador; // El identificador de la partida
	tPartida* enlace; // Puntero a la partida de la lista de partidas
}tParIdEn;

typedef tParIdEn tArray[MAX_PAR_US];

typedef struct{
	tArray lista;
	int cont;
}tListaAccesoPartidas;

// Inicia la lista vacía.
void iniciar(tListaAccesoPartidas &lista);
// Comprueba si la lista está llena.
bool llena(tListaAccesoPartidas const &lista);
// Dado un elemento, si la lista no esta llena, lo inserta al final de la lista.
bool insertar(tListaAccesoPartidas &lista, tParIdEn par);
// Dado un 'id' de partida, lo busca en la lista y si lo encuentra lo elimina. !Ojo, mirar enunciado!
bool eliminar(tListaAccesoPartidas &lista, string const &id); 
// Dado un 'id' de partida, lo busca en la lista de partidas en curso.
bool buscarAccesoPartidas(tListaAccesoPartidas const &lista, string const &id, int &pos);
// Desplaza las partidas en curso para eliminar la que haya en 'pos'
void desplazarIzq(tListaAccesoPartidas &lista, int pos);

#endif  // LISTACCESOPARTIDAS_H
