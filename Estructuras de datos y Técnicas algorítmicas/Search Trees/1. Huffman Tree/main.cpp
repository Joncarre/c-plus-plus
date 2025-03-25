//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include "arbin.h"
using namespace std;

const int MAX = 128;
const string FCodificar = "codi.txt";
const string FDecodificar = "deco.txt";

// Estructura de los Nodos del árbol
typedef struct{
	char letra ;
	int freq ;
}HuffmanNode;

// Estructura para la codificación
typedef struct{
	string codigoToLetra;
}tCodigo;

typedef tCodigo tArray_Codificacion[MAX];

// Variable para la decodificación
string letraToCodigo = "";

// Definimos el nuevo operator
bool operator<(const Arbin< HuffmanNode> &a, const Arbin < HuffmanNode>&b){
	return (a.raiz().freq > b.raiz().freq);
}

// Consruimos el árbol
Arbin< HuffmanNode > construirArbol(priority_queue <Arbin< HuffmanNode>> cola){
	Arbin<HuffmanNode>  arbolIzq;
	Arbin<HuffmanNode>  arbolDer;
	int n = cola.size(); 	// tamaño de la cola

	for (int i = n; i > 1 ; i--){
		arbolIzq = cola.top(); cola.pop();
		arbolDer = cola.top(); cola.pop();
		HuffmanNode nodoSuma; nodoSuma.freq = arbolIzq.raiz().freq + arbolDer.raiz().freq;
		Arbin<HuffmanNode> izq(arbolIzq);
		Arbin<HuffmanNode> der(arbolDer);
		Arbin<HuffmanNode> raiz(izq,nodoSuma,der);
		cola.push(raiz);
	}
	return cola.top();
}

// Recorremos el árbol en preorden sacando los códigos de cada letra
void codificacion(tArray_Codificacion &lista, Arbin<HuffmanNode> arbol, string codigo){
	int indice = 0;
	// Si es hoja...
	if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio()){
		indice = arbol.raiz().letra;
		lista[indice].codigoToLetra = codigo;
	}
	else{
		// hijo izquierdo
		codigo.push_back('0');
		codificacion(lista, arbol.hijoIz(), codigo);
		codigo.pop_back();
		// hijo derecho
		codigo.push_back('1');
		codificacion(lista, arbol.hijoDr(), codigo);
		codigo.pop_back();
	}
}

// Recorremos el árbol sacando las letras desde el código
void decodificacion(queue<char> colaDeco, Arbin<HuffmanNode> arbol, string &lista, int &cont){
	char letra;
	// Si es hoja...
	if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio()){
		letra = arbol.raiz().letra; // Sacamos la letra que está en la hoja
		lista = lista + letra;
		cont--;
	}
	else{
		if (colaDeco.front() == '0'){
			colaDeco.pop(); // Sacamos el elemento
			decodificacion(colaDeco, arbol.hijoIz(), lista, cont);  // Y llamada recursiva al hijo izquierdo
		}
		else{
			colaDeco.pop(); // Sacamos el elemento
			decodificacion(colaDeco, arbol.hijoDr(), lista, cont);  // Y llamada recursiva al hijo derecho
		}
	}
}

// Mostramos el menú para codificar/decodificar
int menu(){
	int opcion;
	do {
		cout << endl << "Elige una opcion: " << endl;
		cout << "1. Codificar el fichero " << FCodificar << " (se llama asi por defecto)." << endl;
		cout << "2. Decodificar el dichero " << FDecodificar << " (se llama asi por defecto)." << endl;
		cout << "0. Salir " << endl;
		cout << "Opcion: ";
		cin >> opcion;
		if ((opcion < 0) || (opcion > 2)) {
			cout << "Opcion no valida!" << endl;
		}
	} while ((opcion < 0) || (opcion > 2));

	return opcion;
}

int main(){
	bool salir = false;
	ifstream archivo;
	priority_queue <Arbin<HuffmanNode>> cola;
	Arbin< HuffmanNode> arbol;
	List<HuffmanNode>*lista;
	queue<char> colaDeco;
	char c;
	int contador = 0;

	while (!salir){
		int op = menu();
		switch (op){
		case 1:
			// ---------- CODIFICAR ----------
			archivo.open(FCodificar); // Comprobamos que existe el archivo 'codi.txt'
			if (!archivo.is_open()){ // Comprobamos que está abierto
				cout << "No existe el fichero." << endl;
				salir = true;
			}
			else {
				int frecs[MAX];
				char c;
				// Inicializamos todas las frecuencias a 0
				for (int i = 0; i < MAX; i++){
					frecs[i] = 0;
				}
				archivo.get(c); // Obtenemos el primer caracter
				while (!archivo.fail()){ // Mientras la lectura del flujo de caracteres no falle...
					frecs[c] ++; // Según su valor en ASCII (que será su índice) aumentamos su frecuencia
					archivo.get(c);
				}

				// Leemos las letra/frecuencia y rellenamos la cola
				for (int i = 0; i < MAX; i++) {
					if (frecs[i] != 0){
						HuffmanNode nodo;
						nodo.letra = char(i);
						nodo.freq = frecs[i];
						Arbin<HuffmanNode> raiz(nodo);
						cola.push(raiz);
						contador++;
					}
				}
				arbol = construirArbol(cola);
				tArray_Codificacion listaCodi;
				string cod = "";
				codificacion(listaCodi, arbol, cod);
				cout << endl << "El fichero codificado es: ";
				for (int i = 0; i < MAX; i++){
					if (listaCodi[i].codigoToLetra != ""){
						cout << listaCodi[i].codigoToLetra;
					}
				}
				cout << endl;
			}
			archivo.close();
			break;
		case 2:
			// ---------- DECODIFICAR ----------
			archivo.open(FDecodificar); // Comprobamos que existe el archivo 'deco.txt'
			if (!archivo.is_open()){ // Comprobamos que está abierto
				cout << "No existe el fichero." << endl;
				salir = false;
			}
			else {
				archivo.get(c); // Obtenemos el primer caracter
				while (!archivo.fail()){ // Mientras la lectura del flujo de caracteres no falle...
					colaDeco.push(c); // Metemos cada 'c' en la cola (que es un código)
					archivo.get(c);
				}
				string listaDeco;
				while (contador > 0 ){
					decodificacion(colaDeco, arbol, listaDeco, contador);
				}
				cout << endl << "El fichero decodificado es: ";
				for (int i = 0; i < listaDeco.size(); i++){
					cout << listaDeco[i];
				}
				cout << endl;
			}
			archivo.close();
			break;
		case 0:
			salir = true;
			break;
		}
	}

	system("PAUSE");
	return 0;
}


