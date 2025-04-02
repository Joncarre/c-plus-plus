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
// Complexity: O(N), where N is the number of characters (could be improved if we read word by word)
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
			indice++; // Read the space between words
			if (palabra.length() > 2){ // If the word has more than 2 letters...
				if (arbol.contains(palabra)){ // If the word is already in the tree...
					bool encontrado = false;
					int j = 0;
					vector<int> lista = arbol.at(palabra);
					while (j < lista.size()){ // We will search the ENTIRE vector to see if it has appeared in this line
						if (lista[j] == i + 1) // If the word has already appeared in the current line...
							encontrado = true;
						j++;
					}
					if (!encontrado){
						lista.push_back(i + 1); // Add the new line where the word appears
						arbol.insert(palabra, lista); // And update the tree node
					}
				}
				else{ // If the word is not in the tree...
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
// Complexity: O(N), due to the call to leerArbol()
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
