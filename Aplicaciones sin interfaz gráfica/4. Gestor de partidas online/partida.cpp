//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "partida.h"
using namespace std;

void abandonar(tPartida & partida){
	partida.actualizacion = fechaActual();
	partida.estadoPartida = Terminada;
}

bool aplicarJugada(tPartida & partida, int col){
	bool exito = true;

	if (aplicarJugada(partida.juego, col))
		if (partida.juego.estado != Jugando)
			abandonar(partida);
	else
		exito = false;

	return exito;
}

void nueva(tPartida & partida, string const& jugador1, string const& jugador2){
	tFecha fechaNueva = fechaActual();
	int fecha = int(fechaNueva);
	partida.id_Partida = to_string(fecha) + "_" + jugador1 + "_" + jugador2;
	partida.id_Partida = "prueba";
	partida.jugador1 = jugador1;
	partida.jugador2 = jugador2;
	partida.inicio = fechaNueva;
	partida.actualizacion = fechaNueva;
	partida.estadoPartida = tEstadoPartida(0);
	iniciar(partida.juego);
}

bool cargar(tPartida & partida, ifstream & archivo){
	bool exito = true;
	int estadoPartida;

	archivo >> partida.id_Partida;
	archivo >> partida.jugador1;
	archivo >> partida.jugador2;
	archivo >> partida.inicio;
	archivo >> partida.actualizacion;
	archivo >> estadoPartida;
	partida.estadoPartida = tEstadoPartida(estadoPartida);
	cargar(partida.juego, archivo); // Usamos la función cargar() ya implementada

	if (archivo.fail()) // Si ha fallado la lectura de datos devolvemos 'false'
		exito = false;

	return exito;
}

void guardar(tPartida const& partida, ofstream & archivo){

	tEstadoPartida estadoPartida;
	tEstado estadoConecta4;
	tTurno turnoConecta4;
	 
	archivo << partida.id_Partida << endl;
	archivo << partida.jugador1 << endl;
	archivo << partida.jugador2 << endl;
	archivo << partida.inicio << " " << partida.actualizacion << endl;
	estadoPartida = partida.estadoPartida;
	archivo << int(estadoPartida) << endl;
	guardar(partida.juego, archivo); // Usamos la funcion guardar() ya implementada
	cout << endl;
}
