//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#ifndef LISTACCESOPARTIDAS_H
#define LISTACCESOPARTIDAS_H

#include <string>
#include <iostream>
using namespace std;

const int MAX_PAR_US = 3;

typedef struct {
	string identificador; // El identificador de la partida
	int enlace; // El índice en el que se encuentra dentro de la lista de partidas del gestor
}tParIdEn;

typedef tParIdEn tArray[MAX_PAR_US];

typedef struct{
	tArray lista;
	int cont;
}tListaAccesoPartidas;

void iniciar(tListaAccesoPartidas &lista); // Inicia la lista vacía.
bool llena(tListaAccesoPartidas const &lista); // Comprueba si la lista está llena.
bool insertar(tListaAccesoPartidas &lista, tParIdEn par); // Dado un elemento, si la lista no esta llena, lo inserta al final de la lista.
bool eliminar(tListaAccesoPartidas &lista, string const &id); // Dado un 'id' de partida, lo busca en la lista y si lo encuentra lo elimina. !Ojo, mirar enunciado! 
bool buscarAccesoPartidas(tListaAccesoPartidas const &lista, string const &id, int &pos); // Dado un 'id' de partida, lo busca en la lista de partidas en curso.

#endif  // LISTACCESOPARTIDAS_H
