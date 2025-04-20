//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <string>
#include <iostream>
#include "gestor.h"
using namespace std;

void menuRegistro(tGestor &gestor); // Muestra y gestiona el menú inicial de la aplicación.
void mostrarDatoUsu(tGestor &gestor); // Si el usuario de la sesión tiene avisos, los muestra y pregunta si quiere eliminarlos.
void menuUsuario(tGestor &gestor); // Muestra y gestiona el menú principal de una sesión de usuario.
void mostrarPartidasEnCurso(tGestor &gestor); // Muestra las cabecerasde cada una de las partias en curso del usuario de la sesión.
void elegirPartida(tGestor &gestor); // Solicita un número válido de partida (de la lista mostrada) y lo apunta como partida seleccionada.
void menuPartida(tGestor &gestor); // Muestra y gestiona el menú de una partida.
void leerJugada(int &col); // Solicita y devuelve una columna válida.


int main(){
	tGestor gestor;
	if (arrancar(gestor)){ // Se cargan los datos
		menuRegistro(gestor); // Comienza todo el flujo que va mostrando los menús y sus opciones
		apagar(gestor); // Al finalizar, se guardan los datos
	}
	else
		cout << "Error al arrancar el gestor." << endl << endl;
		
	system("PAUSE");
	return 0;
}

void menuPartida(tGestor &gestor){
	int opcion;
	cout << endl << endl << "1. Jugar" << endl;
	cout << "2. Abandonar" << endl;
	cout << "0. Salir" << endl << endl;
	cout << "Elija una opcion: ";
	cin >> opcion;

	switch (opcion)
	{
	case 0:
		break;
	case 1:
		int col;
		leerJugada(col);
		jugarPartida(gestor, col);
		break;
	case 2:
		abandonarPartida(gestor);
		break;
	}
}

void leerJugada(int &col){
	bool salir = false;
	do{
		cout << "Introduce la columna: ";
		cin >> col;
		if (col < 0 || col > COLS)
			cout << "Columna incorrecta!" << endl;
		else
			salir = true;
	} while (!salir);
	--col;
}

void mostrarPartidasEnCurso(tGestor &gestor){
	// Hay que mostrar la columnas con el set (como en fecha.cpp)
	cout << endl << "MENU USUARIO" << endl << endl;
	cout << "#  T  Jugador1     Jugador2          Fecha" << endl;
	cout << "-------------------------------------------------------" << endl;
	for (int i = 0; i < gestor.listaUsuarios.lista[gestor.usuarioActivo].lista.cont; i++){
		cout << cabecera(gestor, i) << endl;
	}
	cout << endl;
}

void menuUsuario(tGestor &gestor){
	int opcion;
	mostrarPartidasEnCurso(gestor);

		do {
			cout << "	1. Ver partida" << endl;
			cout << "	2. Nueva partida" << endl;
			cout << "	3. Partidas por actualizacion" << endl;
			cout << "	4. Partidas por turno y fecha" << endl;
			cout << "	0. Salir" << endl << endl;
			cout << "Elija una opcion: ";
			cin >> opcion;
			if ((opcion < 0) || (opcion > 4)) {
				cout << "Opcion no valida!" << endl << endl;
			}
		} while ((opcion < 0) || (opcion > 4));

		switch (opcion)
		{
		case 0:
			cout << "Volviendo al menu anterior..." << endl;
			break;
		case 1:
			elegirPartida(gestor);
			menuPartida(gestor);
			menuUsuario(gestor);
			break;
		case 2:
			nuevaPartida(gestor);
			menuUsuario(gestor);
			break;
		case 3:
			ordenar_Fecha(gestor);
			menuUsuario(gestor);
			break;
		case 4:
			ordenar_Fecha(gestor);
			ordenar_Turno(gestor);
			menuUsuario(gestor);
			break;
		}
}

void mostrarDatoUsu(tGestor &gestor){
	char borrar;
	string aviso;

	if (tieneAvisos(gestor, aviso)){ // Esta función me devuelve los avisos en 'aviso' y sólo faltaría mostrarlos
		for (int i = 0; i < aviso.size(); i++){ // Obtenemos el tamaño del string
			if (aviso[i] == '\n')	// Si se lee un '\n' saltamos de línea
				cout << endl;
			else
				cout << aviso[i]; // Si no, imprimimos el caracter
		}

		cout << endl << "Quiere borrar los avisos (S/N)? ";
		cin >> borrar;
		if (tolower(borrar) == 's')
			limpiarAvisos(gestor);
	}

	cout << endl << "Resumen de actividad" << endl;
	cout << "--------------------" << endl;

	// IMPORTANTE: como ya hemos mostrados los avisos, podemos aprovechar esa variable y usarla para mostrar el resumen de actividad
	aviso = resumenActividad(gestor);

	for (int i = 0; i < aviso.size(); i++){
		if (aviso[i] == '\n')
			cout << endl;
		else
			cout << aviso[i];
	}
}

void menuRegistro(tGestor &gestor){
	int opcion;
	bool salir = false;
	string idUsu;
	string clave;

		do {
			cout << endl << "MENU REGISTRO" << endl << endl;
			cout << "	1. Acceder a mi cuenta" << endl;
			cout << "	2. Registrarse" << endl;
			cout << "	0. Salir" << endl << endl;
			cout << "Elija una opcion: ";
			cin >> opcion;
			if ((opcion < 0) || (opcion > 2)) {
				cout << "Opcion no valida!" << endl << endl;
			}
		} while ((opcion < 0) || (opcion > 2));

		switch (opcion)
		{
		case 0:
			cout << "Saliendo de la aplicacion..." << endl;
			break;
		case 1:
			cout << endl << "ACCESO" << endl;
			cout << "	Nombre de usuario: "; cin >> idUsu;
			cout << "	Clave: "; cin >> clave; cout << endl;
			if (!iniciarSesion(gestor, idUsu, clave)){
				menuRegistro(gestor);
			}
			else{
				mostrarDatoUsu(gestor);
				menuUsuario(gestor);
				menuRegistro(gestor);
			}

			break;
		case 2:
			cout << endl << "REGISTRO" << endl;
			cout << "	Nombre de usuario: "; cin >> idUsu;
			cout << "	Clave: "; cin >> clave; cout << endl;
			crearCuenta(gestor, idUsu, clave);
			menuRegistro(gestor);
			break;
		}
}

void elegirPartida(tGestor &gestor){
	int eleccion;
	int partidasEnCurso = gestor.listaUsuarios.lista[gestor.usuarioActivo].lista.cont;
	
	do {
		cout << endl << "Elija una partida (0 para salir): ";
		cin >> eleccion;
		if ((eleccion < 0) || (eleccion > partidasEnCurso)) {
			cout << "Opcion no valida!" << endl << endl;
		}
	} while ((eleccion < 0) || (eleccion > partidasEnCurso));

	if (eleccion != 0){ // Si la opción no ha sido salir, entonces es que ha elegido una partida correcta
		// Actualizamos la partida activa (que es la que el usuario ha elegido)
		// IMPORTANTE: el 'eleccion - 1' es porque 'cont' indica cuántas partidas hay en curso, no hasta que posición está ocupada la lista de partidas en curso
		gestor.partidaActiva = gestor.listaUsuarios.lista[gestor.usuarioActivo].lista.lista[eleccion - 1].enlace;
		mostrarPartida(gestor); // Y mostramos la partida seleccionada
	}
}

