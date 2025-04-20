//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "listaUsuarios.h"
#include "checkML.h"
using namespace std;
//-----------------------------------------------------------------------------------------------------------------------
void redimensionar(tListaUsuarios &usuarios, int dim){
	if (dim > usuarios.dim){
		tUsuario *aux = new tUsuario[dim]; // Creamos un puntero 'aux' que podrá apuntar a 'dim' usuarios
		for (int i = 0; i < usuarios.cont; i++)
			aux[i] = usuarios.lista[i]; // Hacemos que 'aux' apunte a cada usuario de la lista
		usuarios.dim = dim; // Aumentamos la dimension de la lista de usuarios
	//	for (int i = 0; i < usuarios.cont; i++)
	//		delete usuarios.lista[i]; // Destruimos todo el espacio que ocupada la lista antigüa
		usuarios.lista = new tUsuario[usuarios.dim];
		for (int i = 0; i < usuarios.cont; i++)
			usuarios.lista[i] = aux[i];
		//*usuarios.lista = aux;
	}
}
//-----------------------------------------------------------------------------------------------------------------------
void destruir(tListaUsuarios &usuarios){
	delete[] usuarios.lista;
	usuarios.lista = nullptr;
	usuarios.cont = usuarios.dim = 0;
}
//-----------------------------------------------------------------------------------------------------------------------
void iniciar(tListaUsuarios &usuarios, int dim) {
	usuarios.cont = 0;
	if (dim > usuarios.dim){
		usuarios.dim = dim;
		usuarios.lista = new tUsuario[dim]; // Reservamos espacio
	}
}
//-----------------------------------------------------------------------------------------------------------------------
bool buscarUsuarioEsperando(tListaUsuarios const &usuarios, tNivel nivel, int &pos){
	bool encontrado = false;
	int i = 0;
	while (i < usuarios.cont && !encontrado){
		if (usuarios.lista[i].categoria == nivel && usuarios.lista[i].esperando == true){
			encontrado = true;
			pos = i;
		}
		i++;
	}
	return encontrado;
}
//-----------------------------------------------------------------------------------------------------------------------
bool insertar(tListaUsuarios &usuarios, tUsuario /*const*/ &usuario, int &pos){
	bool exito = true;
	int nuevaDimension;
	if (usuarios.cont == usuarios.dim){ // Si la lista de usuarios está llena...
		nuevaDimension = (usuarios.dim * 3) / 2 + 1;
		redimensionar(usuarios, nuevaDimension); // Se redimensiona siguiendo la fórmula
	}
		 // Reservamos espacio para el nuevo usuario que se va a insertar
	desplazarDerecha(usuarios, pos); // Desplazamos para insertarlo y que quede ordenado por 'nombre'
	usuarios.lista[pos] = usuario; // Hacemos que la posición 'pos' de la lista apunte a ese nuevo usuario
	usuarios.cont++;

	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
void desplazarDerecha(tListaUsuarios &usuarios, int pos){
	for (int i = usuarios.cont; i > pos; i--)
		usuarios.lista[i] = usuarios.lista[i - 1];
}
//-----------------------------------------------------------------------------------------------------------------------
bool buscar(tListaUsuarios const &usuarios, string const &idUser, int &pos){
	// O(log2 N) Implementación de la búsqueda binaria
	bool encontrado = false;
	int ini = 0, fin = usuarios.cont - 1, mitad;
	while ((ini <= fin) && !encontrado){
		mitad = (ini + fin) / 2;
		if (idUser < usuarios.lista[mitad].nombre)
			fin = mitad - 1;
		else if (idUser > usuarios.lista[mitad].nombre)
			ini = mitad + 1;
		else
			encontrado = true;
	}

	if (encontrado)
		pos = mitad;
	else
		pos = ini;

	return encontrado;
}
//-----------------------------------------------------------------------------------------------------------------------
bool cargar(tListaUsuarios &usuarios, ifstream &archivo){
	bool exito = true;
	int numElementos;
	archivo >> numElementos; // Leemos el número de elementos que tiene la lista (donde numElementos es el número de usuarios)
	iniciar(usuarios, numElementos); // Inicializamos la lista dinámica de usuarios

	for (int i = 0; i < numElementos; i++){
		cargar(usuarios.lista[i], archivo); // Para cada posición de la lista, rellenamos los datos de un usuario
		usuarios.cont++; // E incrementamos el contador de usuarios
	}
	return exito;
}
//-----------------------------------------------------------------------------------------------------------------------
void guardar(tListaUsuarios const &usuarios, ofstream &archivo){
	archivo << usuarios.cont << endl; // Metemos el primer número que índica el número de usuarios que vamos a guardar
	for (int i = 0; i < usuarios.cont; i++){ // Obtenemos el número de usuarios gracias a 'cont'
		guardar(usuarios.lista[i], archivo); // Y para cada usuario leído guardamos sus datos
	}
}
