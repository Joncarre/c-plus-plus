//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "listaPartidas.h"
#include "checkML.h"
using namespace std;
//-----------------------------------------------------------------------------------------------------------------------
void destruir(tListaPartidas &partidas){
	for (int i = 0; i < partidas.tam; i++){
		delete partidas.lista[i];
		partidas.lista[i] = nullptr;
	}
	partidas.cont = 0;
	partidas.tam = 0;
}
//-----------------------------------------------------------------------------------------------------------------------
void iniciar(tListaPartidas &partidas) {
	partidas.cont = 0;
	partidas.tam = DIM_partida;
	for (int i = 0; i < partidas.tam; i++){
		partidas.lista[i] = new tPartida;
	}
}
//-----------------------------------------------------------------------------------------------------------------------
bool insertar(tListaPartidas &partidas, tPartida const &partida){
	bool exito = true;
	if (partidas.cont == partidas.tam)
		exito = false;
	else {
		*partidas.lista[partidas.cont] = partida; // Se inserta al final de la lista de partidas
		partidas.cont++;
	}
	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
bool cargar(tListaPartidas &partidas, ifstream &archivo){
	bool exito = true;
	int numElementos;
	archivo >> numElementos; // Leemos el número de elementos que tiene la lista (donde numElementos es el número de partidas)
	
	if (numElementos > DIM_partida){ // Si 'numElementos' es mayor que 'DIM_partida', entonces devolvemos 'false'
		exito = false;
	}
	else {
		iniciar(partidas); // Inicializamos la lista dinámica de partidas
		for (int i = 0; i < numElementos; i++){
			cargar(*partidas.lista[i], archivo); // Para cada posición de la lista, rellenamos los datos de una partida
			partidas.cont++; // E incrementamos el contador de partidas
		}
	}
	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
void guardar(tListaPartidas const &partidas, ofstream &archivo){
	int numTerminadas = 0;
	int numEnCurso = partidas.cont;
	for (int i = 0; i < partidas.cont; i++){ // Obtenemos el número de partidas terminadas
		if (partidas.lista[i]->estadoPartida == Terminada)
			numTerminadas++;
	}
	numEnCurso = numEnCurso - numTerminadas;
	ofstream fichero; // Será el fichero 'historico.txt'
	fichero.open("historico.txt");
	archivo << numEnCurso << endl; // Metemos el número de partidas en curso en 'partidas.txt'
	fichero << numTerminadas << endl; // Metemos el número de partidas terminadas en 'historico.txt'
	for (int i = 0; i < partidas.cont; i++){
		if (partidas.lista[i]->estadoPartida == Terminada)
			guardar(*partidas.lista[i], fichero);
		else
			guardar(*partidas.lista[i], archivo); // Y para cada partida leída guardamos sus datos
	}
	fichero.close();
}
