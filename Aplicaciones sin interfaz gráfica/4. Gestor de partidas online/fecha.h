#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <iostream>
#include <ctime>
using namespace std;

typedef time_t tFecha;

// PROTOTIPOS
tFecha fechaActual(); // Consultar la fecha actual.
string stringFecha(tFecha fecha, bool hora); // Mostrar la fecha en formato Año/Mes/Día.


#endif  // FECHA_H