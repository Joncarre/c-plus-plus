//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>
#include "fecha.h"
#include "Conecta4.h"
using namespace std;

typedef enum { Principiante, Medio, Experto } tNivel;
typedef enum { Gana, Pierde, Empata } tResultado;
const int NIVELES = 3;
const string stringNivel[NIVELES] = { "Principiante", "Medio", "Experto" };
const int NRN = 3;

typedef struct {
	string nombre;
	string pass;
	tNivel categoria;
	int racha;
	bool esperando;
	int ganadas, perdidas, empatadas;
	tFecha ultimaConexion;
	string avisos;
}tUsuario;

// Recibe un 'nombre' y 'pass' de usuario  e inicializa todos sus campos.
void iniciar(tUsuario &usuario, string const &id, string const &pas);
// Dado un flujo de archivo, escribe en el flujo los datos de usuario.
void guardar(tUsuario const &usuario, ofstream &archivo);
// Dado un flujo de archivo, lee los datos de un usuario.
bool cargar(tUsuario &usuario, ifstream &archivo);
// Recibe una 'pass' y un 'nombre' y devuelve si la 'pass' es correcta.
bool iniciarSesion(tUsuario &usuario, string const &clave);
// Actualiza el campo avisos añadiendo al final del string una nueva línea con el nuevo aviso.
void actualizarAvisos(tUsuario &usu, string const &aviso);
// Actualiza el campo avisos dejando el string vacío.
void limpiarAvisos(tUsuario &usu);
// Si el usuario no ha usado todas sus partidas en curso, inserta en su lista de partidas la información a la partida'par'.
bool nuevaPartida(tUsuario &usuario);
// Puf, mejor mirar la página 7 del enunciado.
void aplicarFinPartida(tUsuario &usuario, tResultado resultado);
// Reinicia la racha del 'usuario'.
void reiniciarRacha(tUsuario &usuario);
// Actualiza la racha del 'usuario'.
void actualizarRacha(tUsuario &usuario, tResultado resultado);
// Aumenta la categoría del 'usuario'.
void subeCategoria(tUsuario &usuario);
// Disminuye la categoría del 'usuario'.
void bajaCategoria(tUsuario &usuario);

#endif  // USUARIO_H
