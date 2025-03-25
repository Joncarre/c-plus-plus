//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <string>
#include "TreeMap.h"
#include "List.h"
using namespace std;

typedef	string medico;
typedef string paciente;
struct tFecha{ // Este tipo se debe declarar aquí arriba porque si no, no podría redefinirse la función 'operator'
	int dia;
	int hora;
	int min;

	bool operator<(const tFecha &fecha) const{
		if (dia < fecha.dia)
			return true;
		else if (dia == fecha.dia && hora < fecha.hora)
			return true;
		else if (dia == fecha.dia && hora == fecha.hora && min < fecha.min)
			return true;
	}

	bool operator==(const tFecha &fecha) const{
		if (dia == fecha.dia && hora == fecha.hora && min == fecha.min)
			return true;
		else
			return false;
	}
};

typedef class Consultorio{
	public:
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: O(logN), donde N es el número de elementos en el TreeMap de médicos
		void nuevoMedico(medico nombreMedico){
			if (!tMap.contains(nombreMedico)){ // Si no existe el médico, se crea un árbol vacío y se inserta
				TreeMap<tFecha, paciente> subMap;
				tMap.insert(nombreMedico, subMap);
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: O(logN), donde N es el número de nodos (¡siempre que el árbol esté equilibrado!)
		void pideConsulta(paciente nombrePaciente, medico nombreMedico, tFecha fecha){
			if (!tMap.contains(nombreMedico)){
				throw invalid_argument("Medico no existente.");
			}
			else{
				TreeMap<tFecha, paciente> subMap;
				subMap = tMap.at(nombreMedico); // Si el médico existe, dame su árbol de consultas
				if (subMap.contains(fecha)){
					throw invalid_argument("Fecha ocupada.");
				} 
				else {
					subMap.insert(fecha, nombrePaciente); // Insertamos la nueva consulta
					tMap.insert(nombreMedico, subMap); // Y actualizamos el árbol del médico
				}
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: igual
		paciente siguientePaciente(medico nombreMedico){
			if (!tMap.contains(nombreMedico)){
				throw invalid_argument("Medico no existente.");
			}
			else{
				TreeMap<tFecha, paciente> subMap;
				subMap = tMap.at(nombreMedico); // Si el médico existe, dame su árbol de consultas
				if (subMap.empty()){
					throw invalid_argument("No hay pacientes.");
				}
				else{
					TreeMap<tFecha, paciente>::ConstIterator it = subMap.cbegin();
					return it.value();
				}
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: igual
		void atiendeConsulta(medico nombreMedico){
			if (!tMap.contains(nombreMedico)){
				throw invalid_argument("Medico no existente.");
			}
			else{
				TreeMap<tFecha, paciente> subMap;
				subMap = tMap.at(nombreMedico); // Si el médico existe, dame su árbol de consultas
				if (subMap.empty()){
					throw invalid_argument("No hay pacientes.");
				}
				else{
					TreeMap<tFecha, paciente>::ConstIterator it = subMap.cbegin(); // Cogemos el primer paciente
					subMap.erase(it.key()); // Lo eliminamos
					tMap.insert(nombreMedico, subMap); // Y lo volvemos a insertar
				}
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: O()
		List<TreeMap<tFecha, paciente>> listaPacientes(medico nombreMedico, tFecha fecha){
			List<TreeMap<tFecha, paciente>> lista; // Creamos una lista cuyos elementos serán nodos con el par (tFecha, paciente)
			if (!tMap.contains(nombreMedico)){
				throw invalid_argument("Medico no existente.");
			}
			else{
				TreeMap<tFecha, paciente> subMap;
				subMap = tMap.at(nombreMedico);
				TreeMap<tFecha, paciente>::ConstIterator it = subMap.cbegin();
				while (it != subMap.cend()){
					if (it.key().dia == fecha.dia){ // Si el día coincide
						TreeMap<tFecha, paciente> cita;
						cita.insert(it.key(), it.value());
						lista.push_front(cita);
					}
					it.next();
				}
			}
			return lista;
		}

	private:
	TreeMap<medico, TreeMap<tFecha, paciente>> tMap;
};
