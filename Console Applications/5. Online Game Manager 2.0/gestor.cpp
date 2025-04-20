//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "gestor.h"
#include "checkML.h"
using namespace std;

//------------------------------------------- FUNCIONES MENÚ PARTIDA MAIN  ----------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
void abandonarPartida(tGestor &gestor){
	int posGanador, posPerdedor;
	string aviso;
	abandonar(*gestor.listaPartidas.lista[gestor.partidaActiva]);
	if (gestor.listaPartidas.lista[gestor.partidaActiva]->juego.turno == Jugador1){ // Si el 'Jugador 1' abandona...
		buscar(gestor.listaUsuarios, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador1, posPerdedor);
		buscar(gestor.listaUsuarios, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador2, posGanador);
	}
	else if (gestor.listaPartidas.lista[gestor.partidaActiva]->juego.turno == Jugador2){ // Si el 'Jugador 2' abandona...
		buscar(gestor.listaUsuarios, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador1, posGanador);
		buscar(gestor.listaUsuarios, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador2, posPerdedor);
	}
	aviso = "Has perdido una partida contra " + gestor.listaUsuarios.lista[posGanador].nombre + " el " + stringFecha(gestor.listaPartidas.lista[gestor.partidaActiva]->actualizacion, false);
	actualizarAvisos(gestor.listaUsuarios.lista[posPerdedor], aviso);
	aviso = "Has ganado una partida contra " + gestor.listaUsuarios.lista[posPerdedor].nombre + " el " + stringFecha(gestor.listaPartidas.lista[gestor.partidaActiva]->actualizacion, false);
	actualizarAvisos(gestor.listaUsuarios.lista[posGanador], aviso);
	aplicarFinPartida(gestor.listaUsuarios.lista[posGanador], Gana);
	aplicarFinPartida(gestor.listaUsuarios.lista[posPerdedor], Pierde);
	eliminar(gestor.listaAccesoPartidas, gestor.listaPartidas.lista[gestor.partidaActiva]->id_Partida);
}
//-----------------------------------------------------------------------------------------------------------------------
void jugarPartida(tGestor &gestor, int col){
	int posGanador, posPerdedor;
	string aviso;
	aplicarJugada(*gestor.listaPartidas.lista[gestor.partidaActiva], col);
	if (gestor.listaPartidas.lista[gestor.partidaActiva]->estadoPartida == Terminada){ // Si la partida ha terminado...
		// Localizamos las posiciones de los jugadores
		if (gestor.listaPartidas.lista[gestor.partidaActiva]->juego.turno == Jugador1){ // Si ha sido el 'Jugador 1' el ganador...
			buscar(gestor.listaUsuarios, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador1, posGanador);
			buscar(gestor.listaUsuarios, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador2, posPerdedor);
		}
		else if (gestor.listaPartidas.lista[gestor.partidaActiva]->juego.turno == Jugador2){ // Si ha sido el 'Jugador 2' el ganador...
			buscar(gestor.listaUsuarios, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador1, posPerdedor);
			buscar(gestor.listaUsuarios, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador2, posGanador);
		}

		if (gestor.listaPartidas.lista[gestor.partidaActiva]->juego.estado == Ganador){ // Si ha habido un ganador...
			aviso = "Has perdido una partida contra " + gestor.listaUsuarios.lista[posGanador].nombre + " el " + stringFecha(gestor.listaPartidas.lista[gestor.partidaActiva]->actualizacion, false);
			actualizarAvisos(gestor.listaUsuarios.lista[posPerdedor], aviso);
			aplicarFinPartida(gestor.listaUsuarios.lista[posGanador], Gana);
			aplicarFinPartida(gestor.listaUsuarios.lista[posPerdedor], Pierde);
		}
		else{ // Si no hay ganador, entonces hay empate
			aviso = "Has empatado una partida contra " + gestor.listaUsuarios.lista[posGanador].nombre + " el " + stringFecha(gestor.listaPartidas.lista[gestor.partidaActiva]->actualizacion, false);
			actualizarAvisos(gestor.listaUsuarios.lista[posPerdedor], aviso);
			aviso = "Has empatado una partida contra " + gestor.listaUsuarios.lista[posPerdedor].nombre + " el " + stringFecha(gestor.listaPartidas.lista[gestor.partidaActiva]->actualizacion, false);
			actualizarAvisos(gestor.listaUsuarios.lista[posGanador], aviso);
			aplicarFinPartida(gestor.listaUsuarios.lista[posGanador], Empata);
			aplicarFinPartida(gestor.listaUsuarios.lista[posPerdedor], Empata);
		}
		eliminar(gestor.listaAccesoPartidas, gestor.listaPartidas.lista[gestor.partidaActiva]->id_Partida);
	}
}
//-----------------------------------------------------------------------------------------------------------------------
void mostrarPartida(tGestor const &gestor){
	mostrar(gestor.listaPartidas.lista[gestor.partidaActiva]->juego, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador1, gestor.listaPartidas.lista[gestor.partidaActiva]->jugador2);
}
//-----------------------------------------------------------------------------------------------------------------------
bool esSuTurno(tGestor const &gestor){
	bool exito = false;
	tTurno turnoActivo;
	// ¿El jugador activo es el "Jugador 1" o el "Jugador 2"?
	if (gestor.listaUsuarios.lista[gestor.usuarioActivo].nombre == gestor.listaPartidas.lista[gestor.partidaActiva]->jugador1)
		turnoActivo = Jugador1;
	else
		turnoActivo = Jugador2;
	// ¿Coincide el turno actual con ese jugador activo?
	if (gestor.listaPartidas.lista[gestor.partidaActiva]->juego.turno == turnoActivo)
		exito = true;
	return exito;
}

//------------------------------------------- FUNCIONES MENÚ USUARIO DEL MAIN  ------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
string cabecera(tGestor &gestor, int i){
	apuntaPartida(gestor, i); // Actualizamos la partida activa (la que vamos a procesar)

	ostringstream flujo;
	string tieneTurno;
	string indice = to_string(i + 1);

	if (esSuTurno(gestor))
		tieneTurno = "*";
	else
		tieneTurno = " ";

	string jugador1 = gestor.listaPartidas.lista[gestor.partidaActiva]->jugador1;
	string jugador2 = gestor.listaPartidas.lista[gestor.partidaActiva]->jugador2;
	string fecha = stringFecha(gestor.listaPartidas.lista[gestor.partidaActiva]->actualizacion, true);/*stringFecha(gestor.listaPartidas.lista[gestor.partidaActiva]->inicio, true);*/

	flujo << indice + "  " + tieneTurno + "  " + jugador1 + "            " + jugador2 + "                 " + fecha;
	return flujo.str();
}
//-----------------------------------------------------------------------------------------------------------------------
bool nuevaPartida(tGestor &gestor){
	bool exito = true;
	tPartida partida;
	tParIdEn partidaEnCurso;
	int pos;
	// Si no tiene la lista de partidas en curso llena y no está esperando...
	if (gestor.listaAccesoPartidas.cont < MAX_PAR_US && gestor.listaUsuarios.lista[gestor.usuarioActivo].esperando == false){
		if (buscarUsuarioEsperando(gestor.listaUsuarios, gestor.listaUsuarios.lista[gestor.usuarioActivo].categoria, pos)){ // Buscamos un oponente
			nueva(partida, gestor.listaUsuarios.lista[gestor.usuarioActivo].nombre, gestor.listaUsuarios.lista[pos].nombre); // Creamos una partida con los dos oponentes
			if (insertar(gestor.listaPartidas, partida)){ // Insertamos la partida en la lista de partidas
				partidaEnCurso.enlace = new tPartida; // Reservamos espacio en memoria
				partidaEnCurso.enlace = gestor.listaPartidas.lista[gestor.listaPartidas.cont - 1]; // Hacemos que el puntero apunte a la dirección de memoria de la partida en la posición 'cont - 1'
				partidaEnCurso.identificador = gestor.listaPartidas.lista[gestor.listaPartidas.cont - 1]->id_Partida; // Y le asigno el 'id_Partida'
				// Si alguno de los dos jugadores tiene la lista de partidas en curso llena...
				if (!nuevaPartida(gestor.listaUsuarios.lista[gestor.usuarioActivo])){
					exito = false;
				}
			}
			else{
				cout << "No hay hueco en la lista de partidas." << endl;
				exito = false;
			}
		}
		else{
			gestor.listaUsuarios.lista[gestor.usuarioActivo].esperando = true;
			cout << gestor.listaUsuarios.lista[gestor.usuarioActivo].nombre << " no estaba esperando, pero ahora si lo esta." << endl;
			exito = false;
		}
	}
	else{
		exito = false;
		cout << "Este jugador no admite mas partidas." << endl;
	}
	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
void apuntaPartida(tGestor &gestor, int posParEnCurso){
	bool exito = false;
	int pos = 0;
	while (pos < gestor.listaPartidas.cont && !exito){ // Búscamos el 'id_Partida' de la partida 'posParEnCurso' en la lista de partidas
		if (gestor.listaPartidas.lista[pos]->id_Partida == gestor.listaAccesoPartidas.lista[posParEnCurso].enlace->id_Partida)
			exito = true;
		else
			pos++;
	}
	gestor.partidaActiva = pos; // Y esa posición será la posición que ocupa la 'partidaActiva'
}
//-----------------------------------------------------------------------------------------------------------------------
int partidasUsuario(tGestor &gestor){
	return gestor.listaAccesoPartidas.cont;
}
//-----------------------------------------------------------------------------------------------------------------------
void ordenar_Turno(tGestor &gestor){ // Ordenación por inserción
	tParIdEn elemento; int j;

	for (int i = 1; i < gestor.listaAccesoPartidas.cont; i++){
		elemento = gestor.listaAccesoPartidas.lista[i];
		j = i;
		apuntaPartida(gestor, i); // Hago que la partida activa sea la 'i'
		if (esSuTurno(gestor)){ // Y pregunto si el usuario tiene el turno en la partida 'i'
			apuntaPartida(gestor, j - 1); // Hago que la partida activa sea la 'j - 1'
			while ((j > 0) && (!esSuTurno(gestor))){ // Y pregunto si es el turno del usuario en la partida 'j - 1'
				// Si no es el turno, entonces la partida en la posición 'i' debería adelantarse en la lista de partidas en curso
				gestor.listaAccesoPartidas.lista[j] = gestor.listaAccesoPartidas.lista[j - 1];
				--j;
			}
		}
		gestor.listaAccesoPartidas.lista[j] = elemento; // Restauramos el valor que había en 'j'
	}
}
//-----------------------------------------------------------------------------------------------------------------------
void ordenar_Fecha(tGestor &gestor){ // Ordenación por inserción
	tFecha actualizacion_i; int j;
	tParIdEn elemento;

	for (int i = 1; i < gestor.listaAccesoPartidas.cont; i++){
		elemento = gestor.listaAccesoPartidas.lista[i];
		actualizacion_i = gestor.listaAccesoPartidas.lista[i].enlace->actualizacion;
		// NOTA: La instrucción superior e inferior a este comentario deberían ser lo mismo
		// actualizacion_i = gestor.listaPartidas.lista[gestor.listaUsuarios.lista[gestor.usuarioActivo].lista.lista[i].enlace].actualizacion;
		j = i;
		while ((j > 0) && (actualizacion_i > gestor.listaAccesoPartidas.lista[j - 1].enlace->actualizacion)){
			gestor.listaAccesoPartidas.lista[j] = gestor.listaAccesoPartidas.lista[j - 1];
			--j;
		}
		gestor.listaAccesoPartidas.lista[j] = elemento;
	}
}
//------------------------------------------- FUNCIONES MENÚ REGISTRO DEL MAIN ------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
string resumenActividad(tGestor const &gestor){
	ostringstream flujo;

	flujo << "Partidas ganadas: ";
	flujo << gestor.listaUsuarios.lista[gestor.usuarioActivo].ganadas;
	flujo << '\n';
	flujo << "Partidas perdidas: ";
	flujo << gestor.listaUsuarios.lista[gestor.usuarioActivo].perdidas;
	flujo << '\n';
	flujo << "Partidas empatadas: ";
	flujo << gestor.listaUsuarios.lista[gestor.usuarioActivo].empatadas;
	flujo << '\n';
	flujo << "Nivel actual: ";
	flujo << stringNivel[gestor.listaUsuarios.lista[gestor.usuarioActivo].categoria]; // 'stringNivel' es un array de strings para poder mostrar por pantalla el tipo tNivel
	flujo << '\n';
	flujo << "Racha actual: ";
	flujo << gestor.listaUsuarios.lista[gestor.usuarioActivo].racha;
	flujo << " ganadas";
	flujo << '\n';
	return flujo.str();
}
//-----------------------------------------------------------------------------------------------------------------------
void limpiarAvisos(tGestor &gestor){
	limpiarAvisos(gestor.listaUsuarios.lista[gestor.usuarioActivo]);
}
//-----------------------------------------------------------------------------------------------------------------------
bool tieneAvisos(tGestor const &gestor, string &aviso){
	bool exito = true;
	ostringstream flujo;

	if (gestor.listaUsuarios.lista[gestor.usuarioActivo].avisos == "\n"){
		cout << "No tiene avisos." << endl << endl;
		exito = false;
	}
	else{
		cout << "Tiene avisos:" << endl;
		for (int i = 0; i < gestor.listaUsuarios.lista[gestor.usuarioActivo].avisos.size(); i++){ // Obtenemos el tamaño del string de todos los avisos que haya
			if (gestor.listaUsuarios.lista[gestor.usuarioActivo].avisos[i] == '\n')	// Si se lee un '\n' saltamos de línea
				flujo << '\n';
			else
				flujo << gestor.listaUsuarios.lista[gestor.usuarioActivo].avisos[i]; // Si no, guardamos el caracter
		}
		aviso = flujo.str();
	}
	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
bool iniciarSesion(tGestor &gestor, string const &idUsu, string const &clave){
	bool exito = true;
	int pos;

	if (buscar(gestor.listaUsuarios, idUsu, pos)){ // Si existe el ID del usuario...
		gestor.usuarioActivo = pos; // Seleccionamos la posición que ocupa el usuario activo en la lista de usuarios
		if (iniciarSesion(gestor.listaUsuarios.lista[gestor.usuarioActivo], clave)){ // Si la pass coincide...
			cout << "Ha abierto correctamente una nueva sesion." << endl << endl;
		}
		else{
			cout << "La clave no coincide." << endl << endl;
			exito = false;
		}
	}
	else{
		cout << "No existe el ID del usuario." << endl << endl;
		exito = false;
	}
	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
bool crearCuenta(tGestor &gestor, string const &idUsu, string const &clave){
	bool exito = true;
	tUsuario nuevoUsuario;
	int pos; // Al llamar a buscar(), si es posible crear la cuenta, ya sabremos el lugar en el que debemos crearla y llamaríamos a insertar()
	
	if (!buscar(gestor.listaUsuarios, idUsu, pos)){ // Si no existe el ID del usuario...
		// Inicializo 'nuevoUsuario'
		iniciar(nuevoUsuario, idUsu, clave);
		// Y lo insertamos en la posición que corresponda
		insertar(gestor.listaUsuarios, nuevoUsuario, pos);
		cout << "Se ha registrado correctamente." << endl << endl;
		}
		else{
			cout << "El ID de usuario ya existe." << endl << endl;
			exito = false;
		}
	return exito;
}
//------------------------------------------------- FUNCIONES DE GESTOR -------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
bool arrancar(tGestor &gestor){
	bool exito = true;
	ifstream archivo1;
	ifstream archivo2;

	archivo1.open(fPartida); // Comprobamos que existe el archivo 'partidas.txt'
	if (!archivo1.is_open()){ // Comprobamos que está abierto
		cout << "No existe el fichero." << endl;
		exito = false;
	}
	else {
		if (!cargar(gestor.listaPartidas, archivo1)){ // Si no se ha cargado la lista
			cout << "No se ha cargado la lista de partidas." << endl;
			exito = false;
		}
	}

	archivo1.close(); // Cerramos el archivo porque ahora tendremos que abrir el otro

	archivo2.open(fUsuarios.c_str()); // Comprobamos que existe el archivo 'usuarios.txt'
	if (!archivo2.is_open()){ // Comprobamos que está abierto
		cout << "No existe el fichero." << endl;
		exito = false;
	}
	else {
		if (!cargar(gestor.listaUsuarios, archivo2)){ // Si no se ha cargado la lista
			cout << "No se ha cargado la lista de usuarios." << endl;
			exito = false;
		}
	}
	archivo2.close();
	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
void generarAccesos(tGestor &gestor){
	tParIdEn partidaEnCurso;
	string usuActivo = gestor.listaUsuarios.lista[gestor.usuarioActivo].nombre;
	iniciar(gestor.listaAccesoPartidas);
	// Se podría inicializar
	for (int i = 0; i < gestor.listaPartidas.cont; i++){
		tPartida partida = *gestor.listaPartidas.lista[i];
		if (partida.estadoPartida == EnCurso && (partida.jugador1 == usuActivo || partida.jugador2 == usuActivo)){ // Si la partida i-ésima está en curso...
			partidaEnCurso.identificador = gestor.listaPartidas.lista[i]->id_Partida; // Metemos el id_Partida
			partidaEnCurso.enlace = new tPartida; // Reservamos espacio en memoria de tipo 'tPartida' (que es lo que almacenará 'enlace')
			partidaEnCurso.enlace = gestor.listaPartidas.lista[i];
			insertar(gestor.listaAccesoPartidas, partidaEnCurso);
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------
void apagar(tGestor &gestor){
	ofstream archivo1;
	ofstream archivo2;

	borrarCaducadas(gestor); // Antes de guardar la información en los ficheros, cerramos las partidas caducadas

	archivo1.open("partidas.txt");
	if (!archivo1.is_open()){ // Comprobamos que está abierto
		cout << "No existe el fichero." << endl;
	}
	else {
		guardar(gestor.listaPartidas, archivo1);
		destruir(gestor.listaPartidas); // Destruimos la memoria usada por la lista dinámica
	}

	archivo1.close(); // Cerramos el archivo porque ahora tendremos que abrir el otro

	archivo2.open("usuarios.txt");
	if (!archivo2.is_open()){ // Comprobamos que está abierto
		cout << "No existe el fichero." << endl;
	}
	else {
		guardar(gestor.listaUsuarios, archivo2);
		destruir(gestor.listaUsuarios); // Destruimos la memoria usada por la lista dinámica
	}
	archivo2.close();
}
//-----------------------------------------------------------------------------------------------------------------------
// IMPORTANTE: 30 días son 2.592.000 segundos
void borrarCaducadas(tGestor &gestor){
	for (int i = 0; i < gestor.listaPartidas.cont; i++){ // Recorremos todas las partidas de la lista de partidas
		if (fechaActual() - gestor.listaPartidas.lista[i]->actualizacion > 2592000){ // Si la fecha actual menos la de inicio es superior a 30 días...
			gestor.partidaActiva = i; // Hacemos que la partidaActiva sea 'i' porque si no el abandonarPartida() no funciona
			abandonarPartida(gestor); // IMPORTANTE: que gane el jugador que no tiene el turno es lo mismo a que abandone el jugador que sí tiene el turno
		}
	}
}
