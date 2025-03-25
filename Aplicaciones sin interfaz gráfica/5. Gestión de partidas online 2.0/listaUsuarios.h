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

//const int DIM_usuario = 5;

// Esta lista se encuentra ordenada por el identificador del usuario (nombre)
typedef struct{
	int cont;
	int dim;
	tUsuario *lista;
}tListaUsuarios;

// Carga la lista de usuarios desde el flujo ya abierto.
bool cargar(tListaUsuarios &usuarios, ifstream &archivo);
// Guarda la lista de usuarios en el flujo.
void guardar(tListaUsuarios const &usuarios, ofstream &archivo);
// Dado un 'nombre' de usuario y la lista, devuelve su posición.
bool buscar(tListaUsuarios const &usuarios, string const &idUser, int &pos);
// Añade un usuario a la lista si hay hueco y no hay otro usuario con el mismo nombre.
bool insertar(tListaUsuarios &usuarios, tUsuario /*const*/ &usuario, int &pos);
// Devuelve 'true' y la posición del primer usuario del nivel que está esperando.
bool buscarUsuarioEsperando(tListaUsuarios const &usuarios, tNivel nivel, int &pos);
// Desplaza hacia la derecha para llevar a cabo la inserción.
void desplazarDerecha(tListaUsuarios &usuarios, int pos);
// Inicializa 'usuarios.cont = 0'.
void iniciar(tListaUsuarios &usuarios);
// Redimensiona la lista de usuarios.
void redimensionar(tListaUsuarios &usuarios, int dim);
// Elimina la memoria usada por la lista dinámica de usuarios.
void destruir(tListaUsuarios &usuarios);

#endif  // LISTAUSUARIOS_H
