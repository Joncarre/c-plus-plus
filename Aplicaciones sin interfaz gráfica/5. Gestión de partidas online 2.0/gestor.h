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
#include "ListaAccesoPartidas.h"
using namespace std;

const string fPartida = "partidas.txt";
const string fUsuarios = "usuarios.txt";

typedef struct {
	tListaPartidas listaPartidas;
	tListaUsuarios listaUsuarios;
	tListaAccesoPartidas listaAccesoPartidas;
	int usuarioActivo;
	int partidaActiva;
}tGestor;

// Inicializa el gestor e intenta arrancarlo con la información del sistema.
bool arrancar(tGestor &gestor);
// puf, mejor mirar página 8.
void generarAccesos(tGestor &gestor);
// Apagada el gestor abriendo los ficheros para guardar las listas de usuarios y de partidas del sistema.
void apagar(tGestor &gestor);
// Cierra las partidas con más de 30 días sin actividad.
void borrarCaducadas(tGestor &gestor);

// MENÚ REGISTRO DEL MAIN
// Comprueba si el usuario existe y la contraseña coincide.
bool iniciarSesion(tGestor &gestor, string const &idUsu, string const &clave);
// Crea la cuenta si el 'idUsu' no existe y si hay espacio en la lista.
bool crearCuenta(tGestor &gestor, string const &idUsu, string const &clave);
// Comprueba si el usuario de la sesión tiene avisos.
bool tieneAvisos(tGestor const &gestor, string &aviso);
// Actualiza los avisos del usuario a la cadena vacía.
void limpiarAvisos(tGestor &gestor);
// Devuelve un string con los datos de la actividad del usuario de la sesión.
string resumenActividad(tGestor const &gestor);

// MENÚ USUARIO DEL MAIN
// Ordena por fecha de la última actualización la lista de partidas en curso del usuario de la sesión.
void ordenar_Fecha(tGestor &gestor);
// Ordena igual pero por turno (primero aquellas en las que le toca jugar al usuario de la sesión).
void ordenar_Turno(tGestor &gestor);
// Devuelve el número de partidas en curso del usuario de la sesión.
int partidasUsuario(tGestor &gestor);
// Puf, página 8.
string cabecera(tGestor &gestor, int posEnCurso);
// Puf, página 8.
bool nuevaPartida(tGestor &gestor);
// Dada una posición de la lista de partidas en curso del usuario en sesión, guarda el índice de la partida.
void apuntaPartida(tGestor &gestor, int posParEnCurso);

// MENÚ PARTIDA DEL MAIN
// Muestra el estado de la partida en curso.
void mostrarPartida(tGestor const &gestor);
// Comprueba si es el turno del usuario de la sesión en la partida seleccionada.
bool esSuTurno(tGestor const &gestor);
// Puf, página 9.
void jugarPartida(tGestor &gestor, int col);
// Abandona la partida seleccionada por el usuario y actualiza a sus adversarios.
void abandonarPartida(tGestor &gestor);

#endif  // GESTOR_H
