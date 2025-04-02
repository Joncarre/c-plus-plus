//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include "Consultorio.h"
using namespace std;

int main(){
	Consultorio consultorio;
	string opcion;
	medico nombreMedico;
	paciente nombrePaciente;
	tFecha fecha;
	int numCasos;

	while (true){
		cin >> numCasos;
		for (int i = 0; i < numCasos; i++){

			cin >> opcion;
			if (opcion == "nuevoMedico"){
				cin >> nombreMedico;
				try{
					consultorio.nuevoMedico(nombreMedico);
				}
				catch (invalid_argument& e){
					cout << e.what() << endl << "---" << endl;
				}
			}
			else if (opcion == "pideConsulta"){
				cin >> nombreMedico; cin >> nombrePaciente; cin >> fecha.dia; cin >> fecha.hora; cin >> fecha.min;
				try{
					consultorio.pideConsulta(nombreMedico, nombrePaciente, fecha); 
				}
				catch (invalid_argument& e){
					cout << e.what() << endl << "---" << endl;
				}

			}
			else if (opcion == "siguientePaciente"){
				cin >> nombreMedico;
				try{
					cout << "Siguiente paciente doctor " << nombreMedico << endl;
					cout << consultorio.siguientePaciente(nombreMedico) << endl;
				}
				catch (invalid_argument& e){
					cout << e.what() << endl << "---" << endl;
				}
			}
			else if (opcion == "atiendeConsulta"){
				cin >> nombreMedico;
				try{
					consultorio.atiendeConsulta(nombreMedico);
				}
				catch (invalid_argument& e){
					cout << e.what() << endl << "---" << endl;
				}
			}
			else{
				cin >> nombreMedico; cin >> fecha.dia;
				try{
					List<TreeMap<tFecha, paciente>> lista = consultorio.listaPacientes(nombreMedico, fecha);
					List<TreeMap<tFecha, paciente>>::ConstIterator itLista = lista.cbegin(); // Iterador para ir recorriendo la lista
					cout << "Doctor " << nombreMedico << " dia " << fecha.dia << endl;
					while (itLista != lista.cend()){
						TreeMap<tFecha, paciente> cita; 
						cita = itLista.elem();
						TreeMap<tFecha, paciente>::ConstIterator itCita = cita.cbegin(); // Iterador para mostrar los elementos de la lista, es decir, el par (tFecha, paciente)
						cout << itCita.value() << " " << itCita.key().hora << ":" << itCita.key().min << endl; // Mostramos el paciente con su hora
						itLista.next(); // Pasamos al siguiente elemento de la lista
					}
				}
				catch (invalid_argument& e){
					cout << e.what() << endl << "---" << endl;
				}
			}
		}
	}
	return 0;
}
