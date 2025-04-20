//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include "listaAccesoPartidas.h"
#include "checkML.h"
using namespace std;
//-----------------------------------------------------------------------------------------------------------------------
bool insertar(tListaAccesoPartidas &lista, tParIdEn par){
	bool exito = true;
	if (!llena(lista)){ // Si la lista de acceso a partidas del usuario no está llena...
		// Primero se inserta y después se incrementa. Esto es así porque no hay que olvidar que
		// cuando 'cont' marca 1 significa que la posición 0 del array está ocupada.
		// No tendría sentido que si 'cont' = 0, entonces es que hay 1 elemento en el array.
		lista.lista[lista.cont] = par;
		lista.cont++;
	}
	else
		exito = false;

	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
bool eliminar(tListaAccesoPartidas &lista, string const &id){
	bool exito = true;
	int pos = 0;
	// Simplemente se recorrerá la lista hasta que se encuentre (o no) el 'id' buscado.
	if (buscarAccesoPartidas(lista, id, pos)){ // Si existe una partida con el 'id' dado...
		for (int i = pos; i < lista.cont - 1; i++){
			lista.lista[i] = lista.lista[i + 1];
		}
		lista.cont--;
	}
	else
		exito = false;

	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
bool buscarAccesoPartidas(tListaAccesoPartidas const &lista, string const &id, int &/*in/out*/pos){
	bool exito;
	if (pos < lista.cont){
		if (lista.lista[pos].identificador == id)
			exito = true;
		else
			exito = buscarAccesoPartidas(lista, id, ++pos);
	}
	else exito = false;
	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
bool llena(tListaAccesoPartidas const &lista){
	bool exito = true;

	if (!lista.cont < MAX_PAR_US) // Si 'lista.cont' no es menor que 'MAX_PAR_US'...
		exito = false;

	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
void iniciar(tListaAccesoPartidas &lista){
	lista.cont = 0;
}
//-----------------------------------------------------------------------------------------------------------------------
void desplazarIzq(tListaAccesoPartidas &lista, int pos){
	for (int i = pos; i < lista.cont; i++){
		lista.lista[i] = lista.lista[i + 1]; // Desplazamos todas las partidas y machacamos la partidas que queremos eliminar
	}
}
