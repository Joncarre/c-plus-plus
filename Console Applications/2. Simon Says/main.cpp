//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string> 
#include <fstream>
#include <ctime>
using namespace std;

const int NADIE = 0, MAQUINA = 1, HUMANO = 2, MARCADOR = 2, NUMMONEDAS = 3, MAXRONDAS = 2;
const string CENTINELA = "XXX";

/*
Funcion que devuelve el numero de monedas que saca el jugador humano.
*/
int monedasHumano(int numMONEDAS); 

/*
Funcion que realiza la apuesta del humano segun los limites y reglas.
*/
int apuestaHumano(int eleccionM, int numMonedasH, int numMONEDAS);

/*
Funcion que devuelve el numero de monedas que saca del jugador maquina.
*/
int monedasMaquina(int numMONEDAS);

/*
Funcion que realiza la apuesta de la maquina segun los limites y reglas.
*/
int apuestaMaquina(int numMonedasM, int numMONEDAS);

/*
Funcion que devuelve el valor de quien gana la apuesta.
*/
int quienGana(int numMonedasM, int numMonedasH, int eleccionM, int eleccionH);

/*
Funcion para mostrar el menu del juego y poder elegir una de las opciones.
*/
int menu();

/*
Funcion para cambiar el valor de marcador
*/
int pedirMarcador();

/*
Funcion para cambiar el numero de monedas con el que se juega.
*/
int pedirMonedas();

/*
Funcion para cambiar el valor de marcador en el fichero de texto.
*/
int actualizarFicheroMarcador();

/*
Funcion para cambiar el valor de las monedas en el fichero de texto.
*/
int actualizarFicheroMonedas();

/*
Funcion para mostrar las reglas del juego a traves de un fichero de entrada.
*/
bool mostrarReglas();

/*
Funcion de seleccion segun la opcion elegida en el menu.
*/
void jugada(int marcador, int numMonedas);

/*
Funcion que controla el flujo de ejecución de la partida en el modo de juego Humano vs. Máquina.
*/
void juego(int marcador, int numMonedas);

/*
Funcion que controla el flujo de ejecución de la partida en el modo de juego Máquina vs. Máquina.
*/
void juegoAutomatico(int marcador, int numMonedas);

/*
Punto de entrada del programa.
*/
int main(){

	srand(time(NULL)); // Plantamos la semilla

	ifstream entradaConfigP1;
	entradaConfigP1.open("configP1.txt");

	if (entradaConfigP1.is_open()){

		int marcadorConfigP1, numMonedasConfigP1;
		entradaConfigP1 >> marcadorConfigP1; // Leemos marcador de fichero
		entradaConfigP1 >> numMonedasConfigP1; // Leemos numMonedas de fichero

		jugada(marcadorConfigP1, numMonedasConfigP1);

		entradaConfigP1.close();
	}
	else {
		jugada(MARCADOR, NUMMONEDAS); // Si no se encuentra el fichero, coger los valores constantes
	}

	cout << "Fin del programa" << endl;
	system("PAUSE");
	return 0;
}

int menu(){
	int opcion;
	do {
		cout << "Elige una opcion: " << endl;
		cout << "1 - Cambiar el marcador" << endl;
		cout << "2 - Cambiar el numero de monedas " << endl;
		cout << "3 - Acerca del juego de los chinos" << endl;
		cout << "4 - Jugar una partida" << endl;
		cout << "5 - Jugar una partida automatica" << endl;
		cout << "0 - Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		if ((opcion < 0) || (opcion > 5)) {
			cout << "¡Opcion no valida!" << endl;
		}
	} while ((opcion < 0) || (opcion > 5));

	return opcion;
}

void jugada(int marcador, int numMonedas){
	ifstream entradaConfigP1;
	ofstream salidaConfigP1;
	int marcadorJuego = marcador;
	int monedasJuego = numMonedas;

	int opcion = menu();

	while (opcion != 0){
		switch (opcion){
		case 1:
			marcadorJuego = actualizarFicheroMarcador();

			break;
		case 2:
			monedasJuego = actualizarFicheroMonedas();

			break;
		case 3:
			if (!mostrarReglas())
				cout << "No se ha encontrado el fichero reglas.txt." << endl;

			break;
		case 4:
			juego(marcadorJuego, monedasJuego);
			
			break;
		case 5:
			juegoAutomatico(marcadorJuego, monedasJuego);

			break;

		default:
			cout << "¡Opcion no valida!" << endl;
		
			break;
		}
		opcion = menu();
	}

}


void juego(int marcador, int numMonedas){
	int rondasJugadas = 0;
	int opcionElegida;
	int marcadorJuego = marcador;
	int monedasJuego = numMonedas;
	int ganador;
	bool salir = false;
	int numMonedasM, numMonedasH;
	int eleccionM, eleccionH;
	int marcadorHumano, marcadorMaquina;

	rondasJugadas = 0;
	salir = false;
	marcadorHumano = 0, marcadorMaquina = 0;

	while ((marcadorHumano < marcadorJuego && marcadorMaquina < marcadorJuego) && salir == false){	// Mientras ningún jugador gane marcadorJuego rondas...

		rondasJugadas++;
		numMonedasM = monedasMaquina(monedasJuego);
		numMonedasH = monedasHumano(monedasJuego);
		eleccionM = apuestaMaquina(numMonedasM, monedasJuego);

		cout << "Ahora es tu turno..." << endl;

		eleccionH = apuestaHumano(eleccionM, numMonedasH, monedasJuego);
		ganador = quienGana(numMonedasM, numMonedasH, eleccionM, eleccionH);

		cout << "La Maquina saco: " << numMonedasM << endl;
		cout << "El Humano saco: " << numMonedasH << endl << endl;

		if (ganador == HUMANO){
			cout << "Gana el Humano" << endl;
			marcadorHumano++;
		}
		else if (ganador == MAQUINA){
			cout << "Gana la Maquina" << endl;
			marcadorMaquina++;
		}
		else {
			cout << "No ha ganado nadie" << endl;
		}

		cout << "____________________________________" << endl << endl;

		if (rondasJugadas == MAXRONDAS){
			cout << "Quieres seguir jugando?" << endl;
			cout << "1.- Si" << endl << "2.- No" << endl;
			cin >> opcionElegida;

			if (opcionElegida == 1){
				rondasJugadas = 0;
			}
			else {
				salir = true;
			}
		}
	}

	if (marcadorHumano == marcadorJuego) {
		cout << "El Humano ha ganado la partida!!!" << endl;
		cout << "La Maquina ha ganado " << marcadorMaquina << " ronda<s>" << endl << endl;
	}
	else if (marcadorMaquina == marcadorJuego) {
		cout << "La Maquina ha ganado la partida!!!" << endl;
		cout << "El Humano ha ganado " << marcadorHumano << " ronda<s>" << endl << endl;
	}
}

void juegoAutomatico(int marcador, int numMonedas){

	int marcadorJuego = marcador;
	int monedasJuego = numMonedas;
	int ganador;
	int numMonedasM1, numMonedasM2;
	int eleccionM1, eleccionM2;
	int marcadorMaquina1, marcadorMaquina2;

	marcadorMaquina1 = 0, marcadorMaquina2 = 0;

	while (marcadorMaquina1 < marcadorJuego && marcadorMaquina2 < marcadorJuego){ // Mientras ningún jugador gane marcadorJuego rondas...

		numMonedasM1 = monedasMaquina(monedasJuego);
		numMonedasM2 = monedasMaquina(monedasJuego);

		cout << "La Maquina 1 saco: " << numMonedasM1 << endl;
		cout << "La Maquina 2 saco: " << numMonedasM2 << endl << endl;

		cout << "HABLA LA MAQUINA 1..." << endl;
		eleccionM1 = apuestaMaquina(numMonedasM1, monedasJuego);
		cout << endl;

		cout << "HABLA LA MAQUINA 2..." << endl;
		eleccionM2 = apuestaMaquina(numMonedasM2, monedasJuego);
		cout << endl;

		ganador = quienGana(numMonedasM1, numMonedasM2, eleccionM1, eleccionM2);

		if (eleccionM1 == eleccionM2 && eleccionM1 == numMonedasM1 + numMonedasM2){ // Si ambas apuestas son iguales y han acertado...
			cout << "Empate" << endl;
		}
		else if (ganador == HUMANO){
			cout << "Gana la Maquina 2" << endl;
			marcadorMaquina2++;
		}
		else if (ganador == MAQUINA){
			cout << "Gana la Maquina 1" << endl;
			marcadorMaquina1++;
		}
		else {
			cout << "No ha ganado nadie" << endl;
		}

		cout << "____________________________________" << endl << endl;
	}

	if (marcadorMaquina2 == marcadorJuego) {
		cout << "La Maquina 2 ha ganado la partida!!!" << endl;
		cout << "La Maquina 1 ha ganado " << marcadorMaquina1 << " ronda<s>" << endl << endl;
	}
	else {
		cout << "La Maquina 1 ha ganado la partida!!!" << endl;
		cout << "La Maquina 2 ha ganado " << marcadorMaquina2 << " ronda<s>" << endl << endl;
	}
}

bool mostrarReglas(){
	ifstream fichEntrada;
	string nombArch;
	bool encontrado = false;
	nombArch = "reglas.txt";
	fichEntrada.open(nombArch);

	if (fichEntrada.is_open()){
		encontrado = true;
		getline(fichEntrada, nombArch);
		while (nombArch != CENTINELA && !fichEntrada.eof()){ // Mientras no lleguemos al CENTINELA ni al final del fichero (EOF)...
			if (nombArch == "\n"){
				cout << endl;
			}
			cout << nombArch << " " << endl;
			getline(fichEntrada, nombArch);
		}
		cout << endl;
	}

	fichEntrada.close();

	return encontrado;
}


int monedasHumano(int numMONEDAS){
	int numMonedasH;
	int numMonedasMax = numMONEDAS;

	cout << "Elige el numero de monedas que sacas <" << 0 << " a " << numMonedasMax << ">: " << endl;
	cin >> numMonedasH;

	while (numMonedasH < 0 || numMonedasH > numMonedasMax){
		cout << "Numero de monedas incorrecto... Elige de nuevo: " << endl;
		cin >> numMonedasH;
	}

	return numMonedasH;
}

int monedasMaquina(int numMONEDAS){
	int numMonedasMax = numMONEDAS;
	int numMonedasM = rand() % (numMonedasMax + 1);

	return numMonedasM;
}

int apuestaHumano(int eleccionM, int numMonedasH, int numMONEDAS){
	int eleccionH;
	int eleccionMaq = eleccionM;
	int numMonedasHum = numMonedasH;
	int numMonedasMax = numMONEDAS;
	int monedasTotales = numMonedasMax * 2;

	cout << "Elige el numero de monedas en tu apuesta <" << 0 << " a " << monedasTotales << ">: " << endl;
	cin >> eleccionH;

	while ((eleccionH < numMonedasHum || eleccionH > numMonedasHum + numMonedasMax) || eleccionH == eleccionMaq){

		if (eleccionH < numMonedasHum)
			cout << "No mientas... Elige de nuevo: " << endl;
		else if (eleccionH == eleccionMaq)
			cout << "Tu apuesta debe ser diferente a la de la Maquina... Elige de nuevo: " << endl;
		else
			cout << "Tu apuesta es mayor que las monedas totales... Elige de nuevo: " << endl;

		cin >> eleccionH;
	}
	return eleccionH;
}

int apuestaMaquina(int numMonedasM, int numMONEDAS){
	int numMonedasMaq = numMonedasM;
	int numMonedasMax = numMONEDAS;
	int eleccionM = numMonedasMaq + rand() % ((numMonedasMax + numMonedasMaq + 1) - numMonedasMaq);

	cout << "Creo que hemos sacado " << eleccionM << " moneda<s> entre los dos" << endl;

	return eleccionM;
}

int quienGana(int numMonedasM, int numMonedasH, int eleccionM, int eleccionH){
	int ganador;
	int numMonedasMaq = numMonedasM;
	int numMonedasHum = numMonedasH;
	int eleccionMaq = eleccionM;
	int eleccionHum = eleccionH;

	if (eleccionHum == numMonedasMaq + numMonedasHum)
		ganador = HUMANO;
	else if (eleccionMaq == numMonedasMaq + numMonedasHum)
		ganador = MAQUINA;
	else
		ganador = NADIE;
	return ganador;
}

int pedirMarcador(){
	int marcador;

	cout << "Introduce un nuevo marcador: " << endl;
	cin >> marcador;

	return marcador;
}

int pedirMonedas(){
	int numMonedas;

	cout << "Introduce un nuevo numero de monedas: " << endl;
	cin >> numMonedas;

	return numMonedas;
}

int actualizarFicheroMarcador(){
	ifstream entradaConfigP1;
	ofstream salidaConfigP1;
	int marcadorFichero, monedasFichero;

	entradaConfigP1.open("configP1.txt"); // Abrimos fichero para sólo lectura

	if (entradaConfigP1.is_open()){

		entradaConfigP1 >> marcadorFichero; // Leemos lo que hubiera en marcadorJuego
		entradaConfigP1 >> monedasFichero; // Leemos lo que hubiera en monedasJuego

		marcadorFichero = pedirMarcador(); // Pedimos el nuevo valor que tendrá marcadorJuego

		entradaConfigP1.close();
		salidaConfigP1.open("configP1.txt"); // Abrimos fichero para sólo escritura

		salidaConfigP1 << marcadorFichero << " " << monedasFichero; // Actualizamos marcadorJuego y mantenemos monedasJuego

		salidaConfigP1.close();
	}

	return marcadorFichero;	// Es necesario devolver el valor para actualizar la variable marcadorJuego
}

int actualizarFicheroMonedas(){
	ifstream entradaConfigP1;
	ofstream salidaConfigP1;
	int marcadorFichero, monedasFichero;

	entradaConfigP1.open("configP1.txt"); // Abrimos fichero para sólo lectura

	if (entradaConfigP1.is_open()){

		entradaConfigP1 >> marcadorFichero; // Leemos lo que hubiera en marcadorJuego
		entradaConfigP1 >> monedasFichero; // Leemos lo que hubiera en monedasJuego

		monedasFichero = pedirMonedas(); // Pedimos el nuevo valor que tendrá monedasJuego

		entradaConfigP1.close();
		salidaConfigP1.open("configP1.txt"); // Abrimos fichero para sólo escritura

		salidaConfigP1 << marcadorFichero << " " << monedasFichero; // Actualizamos monedasJuego y mantenemos marcadorJuego

		salidaConfigP1.close();
	}
	return monedasFichero;	// Es necesario devolver el valor para actualizar la variable monedasJuego
}
