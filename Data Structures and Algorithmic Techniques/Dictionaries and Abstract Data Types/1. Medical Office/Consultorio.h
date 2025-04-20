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
struct tFecha{ // This type must be declared up here, otherwise the 'operator' function could not be redefined
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
		// Complexity: O(logN), where N is the number of elements in the TreeMap of doctors
		void nuevoMedico(medico nombreMedico){
			if (!tMap.contains(nombreMedico)){ // If the doctor does not exist, an empty tree is created and inserted
				TreeMap<tFecha, paciente> subMap;
				tMap.insert(nombreMedico, subMap);
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complexity: O(logN), where N is the number of nodes (provided the tree is balanced!)
		void pideConsulta(paciente nombrePaciente, medico nombreMedico, tFecha fecha){
			if (!tMap.contains(nombreMedico)){
				throw invalid_argument("Medico no existente.");
			}
			else{
				TreeMap<tFecha, paciente> subMap;
				subMap = tMap.at(nombreMedico); // If the doctor exists, give me their consultation tree
				if (subMap.contains(fecha)){
					throw invalid_argument("Fecha ocupada.");
				} 
				else {
					subMap.insert(fecha, nombrePaciente); // Insert the new consultation
					tMap.insert(nombreMedico, subMap); // And update the doctor's tree
				}
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complexity: same
		paciente siguientePaciente(medico nombreMedico){
			if (!tMap.contains(nombreMedico)){
				throw invalid_argument("Medico no existente.");
			}
			else{
				TreeMap<tFecha, paciente> subMap;
				subMap = tMap.at(nombreMedico); // If the doctor exists, give me their consultation tree
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
		// Complexity: same
		void atiendeConsulta(medico nombreMedico){
			if (!tMap.contains(nombreMedico)){
				throw invalid_argument("Medico no existente.");
			}
			else{
				TreeMap<tFecha, paciente> subMap;
				subMap = tMap.at(nombreMedico); // If the doctor exists, give me their consultation tree
				if (subMap.empty()){
					throw invalid_argument("No hay pacientes.");
				}
				else{
					TreeMap<tFecha, paciente>::ConstIterator it = subMap.cbegin(); // Get the first patient
					subMap.erase(it.key()); // Remove it
					tMap.insert(nombreMedico, subMap); // And update the doctor's map
				}
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complexity: O()
		List<TreeMap<tFecha, paciente>> listaPacientes(medico nombreMedico, tFecha fecha){
			List<TreeMap<tFecha, paciente>> lista; // Create a list whose elements will be nodes with the pair (tFecha, paciente)
			if (!tMap.contains(nombreMedico)){
				throw invalid_argument("Medico no existente.");
			}
			else{
				TreeMap<tFecha, paciente> subMap;
				subMap = tMap.at(nombreMedico);
				TreeMap<tFecha, paciente>::ConstIterator it = subMap.cbegin();
				while (it != subMap.cend()){
					if (it.key().dia == fecha.dia){ // If the day matches
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
