//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include "TreeMap_RB.h"
using namespace std;

void resuelve(int lineas);
TreeMap<string, vector<int>> leerArbol(int lineas);

// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el número de caracteres (podría mejorarse si vamos leyendo palabra por palabra)
TreeMap<string, vector<int>> leerArbol(int lineas){
	TreeMap<string, vector<int>> arbol;
	string linea;
	string palabra;
	cin.get();
	for (int i = 0; i < lineas; i++){
		getline(cin, linea);
		linea += " \n";
		int indice = 0;
		while (linea[indice] != '\n'){
			palabra = "";
			do{
				palabra.push_back(tolower(linea[indice]));
				indice++;
			} while (linea[indice] != ' ');
			indice++; // Leemos el espacio entre palabras
			if (palabra.length() > 2){ // Si la palabra tiene más de 2 letras...
				if (arbol.contains(palabra)){ // Si la palabra ya está en el árbol...
					bool encontrado = false;
					int j = 0;
					vector<int> lista = arbol.at(palabra);
					while (j < lista.size()){ // Buscaremos en TODO el vector para ver si ha aparecido en esta línea
						if (lista[j] == i + 1) // Si la palabra ya ha aparecido en la línea actual...
							encontrado = true;
						j++;
					}
					if (!encontrado){
						lista.push_back(i + 1); // Metemos la nueva línea en la que aparece la palabra
						arbol.insert(palabra, lista); // Y actualizamos el nodo del árbol
					}
				}
				else{ // Si la palabra no está en el árbol...
					vector<int> nuevaLista;
					nuevaLista.push_back(i + 1);
					arbol.insert(palabra, nuevaLista);
				}
			}
		}
	}
	return arbol;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), por la llamada a leerArbol()
void resuelve(int lineas){
	TreeMap<string, vector<int>> arbol;
	arbol = leerArbol(lineas);

	TreeMap<string, vector<int>>::Iterator it = arbol.begin();
	while (it != arbol.end()){
		cout << it.clave();
		for (int i = 0; i < it.valor().size(); i++){
			cout << " " << it.valor().at(i);
		}
		cout << endl;
		it.operator++();
	}
	cout << "----" << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int lineas;
	cin >> lineas;
	while (lineas > 0){
		resuelve(lineas);
		cin >> lineas;
	}
	//system("PAUSE");
	return 0;
}
