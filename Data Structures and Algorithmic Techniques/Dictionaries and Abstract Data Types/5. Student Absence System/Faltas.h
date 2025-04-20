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
	// COMPLEXITIES: m = subjects, n = students
public:
	//-------------------------------------------------------------------------------------------------------------
	// Complexity: O(m * logn)
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
	// Complexity: O(logn)
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
	// Complexity: O(n)
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
	// Complexity: O()
	List<idAlumno> noFaltas(){
		TreeMap<idAlumno, nada> arbolLimpios;
		HashMap<idAsignatura, TreeMap<idAlumno, numFaltas>>::ConstIterator itAsignatura = listaFaltas.cbegin();
		TreeMap<idAlumno, numFaltas>::ConstIterator itAlumno = itAsignatura.value().cbegin();
		while (itAlumno != itAsignatura.value().cend()){
			arbolLimpios.insert(itAlumno.key(), 0);
			itAlumno.next(); 
		}
		// ------ Up to here we have a list with all students ------
		while (itAsignatura != listaFaltas.cend()){ // Iterate through subjects
			itAlumno = itAsignatura.value().cbegin(); // Each time we start a subject, reset the student iterator to the beginning
			while (itAlumno != itAsignatura.value().cend()){
				if (itAlumno.value() > 0) // If they have more than 0 absences...
					arbolLimpios.erase(itAlumno.key()); // Remove them from the absence tree
				itAlumno.next();
			}
			itAsignatura.next();
		}
		// ------- Up to here we have 'arbolLimpios' with students who have no absences --------
		List<idAlumno> listaLimpios;
		TreeMap<idAlumno, nada>::ConstIterator it = arbolLimpios.cbegin();
		while (it != arbolLimpios.cend()){
			listaLimpios.push_back(it.key());
			it.next();
		}
		return listaLimpios;
	}
	//-------------------------------------------------------------------------------------------------------------
	// Complexity: O(m * logn)
	int totalFaltas(idAlumno idalumno){
		int contadorFaltas = 0;
		HashMap<idAsignatura, TreeMap<idAlumno, numFaltas>>::Iterator itAsignatura = listaFaltas.begin();
		if (!itAsignatura.value().contains(idalumno))
			throw string("El alumno no existe.");
		else{
			TreeMap<idAlumno, numFaltas>::Iterator itAlumno = itAsignatura.value().begin(); // Create the iterator outside the while loop to avoid many copies
			while (itAsignatura != listaFaltas.end()){
				itAlumno = itAsignatura.value().find(idalumno);
				contadorFaltas += itAlumno.value();
				itAsignatura.next();
			}
		}
		return contadorFaltas;
	}
	//-------------------------------------------------------------------------------------------------------------
	// Complexity: O(m) where m is the number of subjects
	void maxFaltas(){
		// Not implemented, read below.
	}
	// What we would do is, instead of having the key 'idAsignatura' in the HashMap, we would have
	// a structure containing 'idAsignatura' and also a counter. This counter (one for each subject)
	// indicates the total number of absences for that subject. Then, when we want to check which subject has the most absences,
	// we simply iterate through all subjects in the HashMap and keep the highest one, which has a cost
	// of O(m) where m is the number of subjects.
	// The structure would be like this:
	typedef struct nuevaClave{
		int faltasTotales;
		idAsignatura idasignatura;
	};
	// And therefore the new data structure to store the data would look like this
	HashMap<nuevaClave, TreeMap<idAlumno, numFaltas>> listaFaltas2;

private:
	HashMap<idAsignatura, TreeMap<idAlumno, numFaltas>> listaFaltas;
};
