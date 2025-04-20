//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "listaPartidas.h"
using namespace std;

bool insertar(tListaPartidas &partidas, tPartida const &partida){
	bool exito = true;

	if (partidas.cont < DIM_partida){ // Si hay menos partidas que la cantidad de partidas que puede haber, entonces es que hay hueco
		// Guardo todos los atributos de la partida en el lugar que indica 'cont'
		partidas.lista[partidas.cont].id_Partida = partida.id_Partida;
		partidas.lista[partidas.cont].jugador1 = partida.jugador1;
		partidas.lista[partidas.cont].jugador2 = partida.jugador2;
		partidas.lista[partidas.cont].inicio = partida.inicio;
		partidas.lista[partidas.cont].actualizacion = partida.actualizacion;
		partidas.lista[partidas.cont].estadoPartida = partida.estadoPartida;
		partidas.lista[partidas.cont].juego = partida.juego; // Copiamos toda la estructura 'juego'
		partidas.cont++; // Incremento 'cont' después de haber insertado en la posición anterior (pues 'cont' se inicializa a 0)
	}
	else{
		exito = false;
	}
	return exito;
}

bool cargar(tListaPartidas &partidas, ifstream &archivo){
	partidas.cont = 0; // Inicializamos el número de partidas
	bool exito = true;
	int numElementos;

	archivo >> numElementos; // Leemos el número de elementos que tiene la lista (donde numElementos es el número de partidas)
	if (numElementos > DIM_partida){ // Y si 'numElementos' es mayor que 'DIM_partida', entonces devolvemos 'false'
		exito = false;
	}
	else {
		for (int i = 0; i < numElementos; i++){
			cargar(partidas.lista[i], archivo); // Para cada posición de la lista, rellenamos los datos de una partida
			partidas.cont++; // E incrementamos el contador de partidas
		}
	}
	return exito;
}

void guardar(tListaPartidas const &partidas, ofstream &archivo){
	archivo << partidas.cont << endl; // Metemos el primer número que índica el número de partidas que vamos a guardar
	for (int i = 0; i < partidas.cont; i++){ // Obtenemos el número de partidas gracias a 'cont'
		guardar(partidas.lista[i], archivo); // Y para cada partida leída guardamos sus datos
	}
}
