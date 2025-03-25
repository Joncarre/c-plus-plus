//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include "HashMap.h"
#include "TreeMap.h"
#include "List.h"

typedef string idAlumno;
typedef string idAsignatura;
typedef int numFaltas;
typedef int nada;

typedef class Faltas{
	// COMPLEJIDADES: m = asignaturas, n = alumnos
public:
	//-------------------------------------------------------------------------------------------------------------
	// Complejidad: O(m * logn)
	void anadirAlumno(idAlumno idalumno){
		HashMap<idAsignatura, TreeMap<idAlumno, numFaltas>>::Iterator itAsignatura = listaFaltas.begin();
		if (itAsignatura.value().contains(idalumno))
			throw string("El alumno ya existe.");
		else{
			while (itAsignatura != listaFaltas.end()){
				itAsignatura.value().insert(idalumno, 0);
				itAsignatura.next();
			}
		}
	}
	//-------------------------------------------------------------------------------------------------------------
	// Complejidad: O(logn)
	void anadirFalta(idAlumno idalumno, idAsignatura idasignatura){
		if (!listaFaltas.contains(idasignatura))
			throw string("La asignatura no existe.");
		else{
			HashMap<idAsignatura, TreeMap<idAlumno, numFaltas>>::Iterator itAsignatura = listaFaltas.find(idasignatura);
			if (!itAsignatura.value().contains(idalumno))
				throw string("El alumno no existe.");
			else{
				TreeMap<idAlumno, numFaltas>::Iterator itAlumno = itAsignatura.value().find(idalumno);
				itAlumno.value()++;
			}
		}
	}
	//-------------------------------------------------------------------------------------------------------------
	// Complejidad: O(n)
	void anadirAsignatura(idAsignatura idasignatura){
		if (listaFaltas.contains(idasignatura))
			throw string("La asignatura ya existe.");
		else{
			HashMap<idAsignatura, TreeMap<idAlumno, numFaltas>>::ConstIterator itAsignatura = listaFaltas.cbegin();
			TreeMap<idAlumno, numFaltas>::ConstIterator itAlumno = itAsignatura.value().cbegin();
			TreeMap<idAlumno, numFaltas> nuevoArbol;
			while (itAlumno != itAsignatura.value().cend()){
				nuevoArbol.insert(itAlumno.key(), 0);
				itAlumno.next();
			}
			listaFaltas.insert(idasignatura, nuevoArbol);
		}
	}
	//-------------------------------------------------------------------------------------------------------------
	// Complejidad: O()
	List<idAlumno> noFaltas(){
		TreeMap<idAlumno, nada> arbolLimpios;
		HashMap<idAsignatura, TreeMap<idAlumno, numFaltas>>::ConstIterator itAsignatura = listaFaltas.cbegin();
		TreeMap<idAlumno, numFaltas>::ConstIterator itAlumno = itAsignatura.value().cbegin();
		while (itAlumno != itAsignatura.value().cend()){
			arbolLimpios.insert(itAlumno.key(), 0);
			itAlumno.next(); 
		}
		// ------ Hasta aquí tenemos una lista con todos los alumnos ------
		while (itAsignatura != listaFaltas.cend()){ // Recorremos las asignaturas
			itAlumno = itAsignatura.value().cbegin(); // Cada vez que empecemos en una asignatura, hay que poner el iterador de alumnos al principio
			while (itAlumno != itAsignatura.value().cend()){
				if (itAlumno.value() > 0) // Si tiene más de 0 faltas...
					arbolLimpios.erase(itAlumno.key()); // Lo borramos del árbol de faltas
				itAlumno.next();
			}
			itAsignatura.next();
		}
		// ------- Hasta aquí tenemos el 'arbolLimpios' con los alumnos que no tienen ninguna falta --------
		List<idAlumno> listaLimpios;
		TreeMap<idAlumno, nada>::ConstIterator it = arbolLimpios.cbegin();
		while (it != arbolLimpios.cend()){
			listaLimpios.push_back(it.key());
			it.next();
		}
		return listaLimpios;
	}
	//-------------------------------------------------------------------------------------------------------------
	// Complejidad: O(m * logn)
	int totalFaltas(idAlumno idalumno){
		int contadorFaltas = 0;
		HashMap<idAsignatura, TreeMap<idAlumno, numFaltas>>::Iterator itAsignatura = listaFaltas.begin();
		if (!itAsignatura.value().contains(idalumno))
			throw string("El alumno no existe.");
		else{
			TreeMap<idAlumno, numFaltas>::Iterator itAlumno = itAsignatura.value().begin(); // Creamos el iterador fuera del while para no hacer muchas copias
			while (itAsignatura != listaFaltas.end()){
				itAlumno = itAsignatura.value().find(idalumno);
				contadorFaltas += itAlumno.value();
				itAsignatura.next();
			}
		}
		return contadorFaltas;
	}
	//-------------------------------------------------------------------------------------------------------------
	// Complejidad: O(m) donde m es el número de asignaturas
	void maxFaltas(){
		// No está implementada, leer lo de abajo.
	}
	// Lo que haríamos sería que, en vez de tener la clave 'idAsignatura' en el HashMap, lo que tendríamos sería
	// una estructura en la que está el 'idAsignatura' y además hay un contador. Este contador (que hay uno para cada asignatura)
	// índica el número total de faltas de esas asignatura. Entonces, cuando queramos mirar qué asignatura tiene más faltas,
	// Simplemente tenemos que recorrer todas las asignaturas del HashMap y quedarnos con la más alta, lo cual tiene un coste
	// de O(m) donde m es el número de asignaturas.
	// La estructura sería como esta:
	typedef struct nuevaClave{
		int faltasTotales;
		idAsignatura idasignatura;
	};
	// Y por lo tanto la nueva estructura para almacenar los datos quedaría así
	HashMap<nuevaClave, TreeMap<idAlumno, numFaltas>> listaFaltas2;

private:
	HashMap<idAsignatura, TreeMap<idAlumno, numFaltas>> listaFaltas;
};
