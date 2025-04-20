//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#ifndef GESTOR_H
#define GESTOR_H

#include <string>
#include <iostream>
#include "listaPartidas.h"
#include "listaUsuarios.h"
using namespace std;

const string fPartida = "partidas.txt";
const string fUsuarios = "usuarios.txt";

typedef struct {
	tListaPartidas listaPartidas;
	tListaUsuarios listaUsuarios;
	int usuarioActivo;
	int partidaActiva;
}tGestor;

//PROTOTIPOS
bool arrancar(tGestor &gestor); // Inicializa el gestor e intenta arrancarlo con la información del sistema.
void generarAccesos(tGestor &gestor); // puf, mejor mirar página 8.
void apagar(tGestor &gestor); // Apagada el gestor abriendo los ficheros para guardar las listas de usuarios y de partidas del sistema.

// MENÚ REGISTRO DEL MAIN
bool iniciarSesion(tGestor &gestor, string const &idUsu, string const &clave); // Comprueba si el usuario existe y la contraseña coincide.
bool crearCuenta(tGestor &gestor, string const &idUsu, string const &clave); // Crea la cuenta si el 'idUsu' no existe y si hay espacio en la lista.
bool tieneAvisos(tGestor const &gestor, string &aviso); // Comprueba si el usuario de la sesión tiene avisos.
void limpiarAvisos(tGestor &gestor); // Actualiza los avisos del usuario a la cadena vacía.
string resumenActividad(tGestor const &gestor); // Devuelve un string con los datos de la actividad del usuario de la sesión.

// MENÚ USUARIO DEL MAIN
void ordenar_Fecha(tGestor &gestor); // Ordena por fecha de la última actualización la lista de partidas en curso del usuario de la sesión.
void ordenar_Turno(tGestor &gestor); // Ordena igual pero por turno (primero aquellas en las que le toca jugar al usuario de la sesión).
int partidasUsuario(tGestor &gestor); // Devuelve el número de partidas en curso del usuario de la sesión.
string cabecera(tGestor &gestor, int posEnCurso); // Puf, página 8.
bool nuevaPartida(tGestor &gestor); // Puf, página 8.
void apuntaPartida(tGestor &gestor, int posParEnCurso); // Dada una posición de la lista de partidas en curso del usuario en sesión, guarda el índice de la partida.

// MENÚ PARTIDA DEL MAIN
void mostrarPartida(tGestor const &gestor); // Muestra el estado de la partida en curso.
bool esSuTurno(tGestor const &gestor); // Comprueba si es el turno del usuario de la sesión en la partida seleccionada.
void jugarPartida(tGestor &gestor, int col); // Puf, página 9.
void abandonarPartida(tGestor &gestor); // Abandona la partida seleccionada por el usuario y actualiza a sus adversarios.


#endif  // GESTOR_H
