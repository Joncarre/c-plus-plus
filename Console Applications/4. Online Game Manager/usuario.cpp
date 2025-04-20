//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include "usuario.h"
using namespace std;

void aplicarFinPartida(tUsuario &usuario, string const& idPar, tResultado resultado){
	if (resultado == Gana){
		usuario.ganadas++;
	}
	else if (resultado == Pierde){
		usuario.perdidas++;
	}
	else{
		usuario.empatadas++;
	}
	actualizarRacha(usuario, resultado);
	eliminar(usuario.lista, idPar); // Y procedemos a eliminar la partida de la lista de partidas en curso
}

void actualizarRacha(tUsuario &usuario, tResultado resultado){
	if (resultado == Gana){ // Si el resultado es 'Gana'...
		if (usuario.racha < 0){ // Si anteriormente tenía alguna partida perdida...
			reiniciarRacha(usuario);
			usuario.racha++;
		}
		else if (usuario.racha == NRN - 1){ // Si le quedaba una partida para ascender de categoría...
			usuario.racha++;
			subeCategoria(usuario);
		}
		else
			usuario.racha++;
	}
	else if (resultado == Pierde){ // Si el resultado es 'Pierde'...
		if (usuario.racha > 0){ // Si anteriormente tenía alguna partida ganada...
			reiniciarRacha(usuario);
			usuario.racha--;
		}
		else if (usuario.racha == -NRN + 1){ // Si le quedaba una partida para descender de categoría...
			usuario.racha--;
			bajaCategoria(usuario);
		}
		else
			usuario.racha--;
	}
	else // Si el resultado es 'Empata'...
		reiniciarRacha(usuario);
}

void subeCategoria(tUsuario &usuario){
	if (usuario.categoria == Principiante){
		usuario.categoria = Medio;
		cout << "Ha subido de categoria a Medio." << endl;
	}
	else if (usuario.categoria == Medio){
		usuario.categoria = Experto;
		cout << "Ha subido de categoria a Experto" << endl;
	}
}

void bajaCategoria(tUsuario &usuario){
	if (usuario.categoria == Experto){
		usuario.categoria = Medio;
		cout << "Ha bajado de categoria a Medio." << endl;
	}
	else if (usuario.categoria == Medio){
		cout << "Ha bajado de categoria a Principiante." << endl;
		usuario.categoria = Principiante;
	}
}

bool nuevaPartida(tUsuario &usuario, tParIdEn const &par){
	bool exito = true;
	if (usuario.lista.cont < MAX_PAR_US){
		usuario.lista.lista[usuario.lista.cont] = par; // Insertamos la partida en la posición
		usuario.lista.cont++; // E incrementamos el 'cont'
		usuario.esperando = false;
	}
	else{
		usuario.esperando = true;
		exito = false;
	}
	return exito;
}

void reiniciarRacha(tUsuario &usuario){
	usuario.racha = 0;
}

void limpiarAvisos(tUsuario &usu){
	usu.avisos = '\n'; // En los avisos ponemos un salto de línea
}

void actualizarAvisos(tUsuario &usu, string const &aviso){
	usu.avisos = usu.avisos + aviso + '\n';
}

bool iniciarSesion(tUsuario &usuario, string const &clave){
	bool exito = true;
	if (usuario.pass == clave)
		usuario.ultimaConexion = fechaActual();
	else
		exito = false;

	return exito;
}

void iniciar(tUsuario &usuario, string const &id, string const &pas){
	usuario.nombre = id;
	usuario.pass = pas;
	usuario.categoria = Principiante;
	usuario.racha = 0;
	usuario.esperando = 0;
	usuario.ganadas = 0;
	usuario.perdidas = 0;
	usuario.empatadas = 0;
	usuario.ultimaConexion = fechaActual();
	usuario.avisos = '\n';
}

bool cargar(tUsuario &usuario, ifstream &archivo){
	bool exito = true;
	int nivelUsuario;
	string aviso;

	archivo >> usuario.nombre;
	archivo >> usuario.pass;
	archivo >> nivelUsuario;
	usuario.categoria = tNivel(nivelUsuario);
	archivo >> usuario.racha;
	archivo >> usuario.esperando;
	archivo >> usuario.ganadas;
	archivo >> usuario.perdidas;
	archivo >> usuario.empatadas;
	archivo >> usuario.ultimaConexion;
	archivo.ignore(INT_MAX, '\n'); // ignore() se utiliza en archivos para descartar hasta '\n' (en este caso) o hasta INT_MAX
	getline(archivo, aviso, '\n');
	while (aviso != "_X_X_X_"){ // Hasta encontrarnos con el centinela seguimos leyendo avisos (y concatenándolos)
		usuario.avisos = usuario.avisos + aviso + '\n';
		getline(archivo, aviso, '\n');
	}

	if (archivo.fail()) // Si ha fallado la lectura de datos devolvemos 'false'
		exito = false;
	else // Si no ha fallado...
		iniciar(usuario.lista); // Devolvemos 'true' e inicializamos la lista de partidas en curso del usuario

	return exito;
}

void guardar(tUsuario const &usuario, ofstream &archivo){
	tNivel nivelUsuario;

	archivo << usuario.nombre << endl;
	archivo << usuario.pass << endl;
	nivelUsuario = usuario.categoria;
	archivo << int(nivelUsuario) << " " << usuario.racha << " " << usuario.esperando << endl;
	archivo << usuario.ganadas << " " << usuario.perdidas << " " << usuario.empatadas << endl;
	archivo << usuario.ultimaConexion << endl;
	if (usuario.avisos == " "){ // Si el usuario no tiene avisos...
		archivo << " " + '\n'; // Metemos un espacio en blanco y un salto de línea
	}
	else{
		for (int i = 0; i < usuario.avisos.size(); i++){ // Obtenemos el tamaño del string de todos los avisos que haya
			if (usuario.avisos[i] == '\n')	// Si se lee un '\n' saltamos de línea
				archivo << endl;
			else
				archivo << usuario.avisos[i]; // Si no, guardamos el caracter
		}
	}
	archivo << "_X_X_X_" << endl;
	cout << endl;
}

