//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <string>
#include <ctime>
#include "HashMap.h"
#include "List.h"
#include "TreeMap.h"
using namespace std;

typedef string ClaveLibro;
typedef struct InfoLibro{
	int disponibles;
	int ventas;
	time_t fecha;
};


typedef class Aplicacion{
	public:
		//---------------------------------------------------------------------------------------------------------------------------------------------
		void nuevoLibro(ClaveLibro nombreLibro, int numEjemplares){
			if (tHash.contains(nombreLibro)){ // Si el libro está en el sistema...
				TreeMap<ClaveLibro, InfoLibro>::Iterator it = tHash.find(nombreLibro);
				it.value().disponibles = it.value().disponibles + numEjemplares;
			}
			else{
				InfoLibro libroNuevo;
				libroNuevo.disponibles = numEjemplares;
				tHash.insert(nombreLibro, libroNuevo);
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		void comprar(ClaveLibro nombreLibro){
				// NOTA: Falta comprobar que el libro existe
			TreeMap<ClaveLibro, InfoLibro>::Iterator it = tHash.find(nombreLibro);
				if (it.value().disponibles == 0){ // Si no hay ejemplares...
					throw out_of_range("No hay ejemplares.");
				}
				else{
					it.value().disponibles--;
					it.value().ventas++;
					it.value().fecha = time(0);
				}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		bool estaLibro(ClaveLibro nombreLibro){
			if (tHash.contains(nombreLibro))
				return true;
			else
				return false;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		void elimLibro(ClaveLibro nombreLibro){
			if (tHash.contains(nombreLibro)){
				tHash.erase(nombreLibro);
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		int numEjemplares(ClaveLibro nombreLibro){
			if (tHash.contains(nombreLibro)){
				TreeMap<ClaveLibro, InfoLibro>::Iterator it = tHash.find(nombreLibro);
				return it.value().disponibles;
			}
			else{
				throw invalid_argument("Libro no existente.");
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		List<ClaveLibro> top10(){

		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		void mostrar(){
			TreeMap<ClaveLibro, InfoLibro>::ConstIterator it = tHash.cbegin();
			while (it != tHash.cend()){
				cout << "Libro: " << it.key() << endl;
				it.next();
			}
		}

	private:
		TreeMap<ClaveLibro, InfoLibro> tHash;
};
