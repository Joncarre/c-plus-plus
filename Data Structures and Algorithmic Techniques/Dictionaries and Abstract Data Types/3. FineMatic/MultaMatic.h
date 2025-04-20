//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include "TreeMap.h"
#include "HashMap.h"
#include <ctime>
using namespace std;

typedef struct InfoTramo{
	TreeMap<string, int> camInicio;
	int tiempoMulta;
	HashMap<string, int> HashMultasTramo;
};

typedef class Aplicacion{
	public:
		//---------------------------------------------------------------------------------------------------------------------------------------------
		void actualizarMultasTotales(string matricula){
			if (HashMultasTotales.contains(matricula)){ // If they had already received another fine (in this or another section)...
				HashMap<string, int>::Iterator it = HashMultasTotales.find(matricula);
				it.value()++; // Increment their fine count
			}
			else{ // If it's the first fine they receive...
				HashMultasTotales.insert(matricula, 1); // Insert them with their first fine
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complexity: O(1) because it's a Hash table
		void insertaTramo(string tramo){
			if (HashTramo.contains(tramo)){
				throw string("El tramo ya existe.");
			}
			else{
				InfoTramo nuevo;
				nuevo.tiempoMulta = 5;
				HashTramo.insert(tramo, nuevo);
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complexity: O(1) + O(logn), therefore O(logn) because it has to insert into the TreeMap 'camInicio'
		void fotoEntrada(string tramo, string matricula, int instante){
			if (!HashTramo.contains(tramo)){
				throw string("Tramo no existente.");
			}
			else{
				HashMap<string, InfoTramo>::Iterator it = HashTramo.find(tramo); // Get the section the car enters
				it.value().camInicio.insert(matricula, instante); // And insert it into the camera that captures cars entering the section
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complexity: O(logn) because it has to search for the time it entered the section, and this search is done in the TreeMap 'camInicio'
		void fotoSalida(string tramo, string matricula, int instante){
			if (!HashTramo.contains(tramo)){
				throw string("Tramo no existente.");
			}
			else{
				HashMap<string, InfoTramo>::Iterator itTramo = HashTramo.find(tramo); // Get the section the car exits
				if (instante - itTramo.value().camInicio.at(matricula) < itTramo.value().tiempoMulta){ // If the current time minus the time the car passed through the tunnel is less than 'tiempoMulta'...
					// Then we must issue a fine. And we check if that license plate already had previous fines
					if (itTramo.value().HashMultasTramo.contains(matricula)){ // If it already had fines...
						HashMap<string, int>::Iterator itMultas = itTramo.value().HashMultasTramo.find(matricula);
						itMultas.value()++; // Increase its fine counter in this section
					}
					else{ // And if it didn't have fines... It means it wasn't in HashMultasTramo and needs to be inserted
						itTramo.value().HashMultasTramo.insert(matricula, 1); // Now that license plate has 1 fine
					}
					actualizarMultasTotales(matricula);
				}
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complexity: O(1) for performing a search in a Hash table
		int multasPorMatricula(string matricula){
			if (!HashMultasTotales.contains(matricula)){
				throw string("La matricula no tiene multas.");
			}
			else{
				HashMap<string, int>::Iterator it = HashMultasTotales.find(matricula);
				return it.value();
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complexity: O(n) where 'n' is the number of fined license plates in the 'tramo'
		HashMap<string, int> multasPorTramos(string tramo){
			if (!HashTramo.contains(tramo)){
				throw string("Tramo no existente");
			}
			else{
				HashMap<string, InfoTramo>::Iterator it = HashTramo.find(tramo);
				return it.value().HashMultasTramo;
			}
		}

	private:
		HashMap<string, InfoTramo> HashTramo;
		HashMap<string, int> HashMultasTotales;
};

