//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include <string>
#include <iostream>
#include "usuario.h"
#include "Conecta4.h"
using namespace std;

const int DIM_usuario = 5;
typedef tUsuario tArray_usuario[DIM_usuario];

// Esta lista se encuentra ordenada por el identificador del usuario (nombre)
typedef struct{
	tArray_usuario lista;
	int cont;
}tListaUsuarios;

bool cargar(tListaUsuarios &usuarios, ifstream &archivo); // Carga la lista de usuarios desde el flujo ya abierto.
void guardar(tListaUsuarios const &usuarios, ofstream &archivo); // Guarda la lista de usuarios en el flujo.
bool buscar(tListaUsuarios const &usuarios, string const &idUser, int &pos); // Dado un 'nombre' de usuario y la lista, devuelve su posición.
bool insertar(tListaUsuarios &usuarios, tUsuario const &usuario, int &pos); // Añade un usuario a la lista si hay hueco y no hay otro usuario con el mismo nombre.
bool buscarUsuarioEsperando(tListaUsuarios const &usuarios, tNivel nivel, int &pos); // Devuelve 'true' y la posición del primer usuario del nivel que está esperando.
void desplazarDerecha(tListaUsuarios &usuarios, int pos); // Desplaza hacia la derecha para llevar a cabo la inserción.

#endif  // LISTAUSUARIOS_H
