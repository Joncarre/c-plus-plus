//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string> 
#include <fstream>
#include <ctime>
#include <ctype.h>
#include <vector>
using namespace std;

const int MAX_COLORES_FACIL = 3; // Se pone a 3 porque el 0 también cuenta.
const int MAX_COLORES_DIFICIL = 6; // Ídem.
const int MAX_COLORES_SEQ = 6;	// Ídem.
const int AYUDAS = 3;
const int MAX_JUGADORES = 10;

enum tModo { Facil, Dificil }; // Modos disponibles para jugar.
enum tColores { Rojo, Verde, Azul, Dorado, Blanco, Marron, Naranja }; // Colores disponibles para jugar.

typedef tColores tSecuencia[MAX_COLORES_SEQ];

typedef struct{
	float puntuacion;
	string nombre;
}tEstructura;

typedef tEstructura tArray[MAX_JUGADORES];	

typedef struct {
	tArray vector;
	int cont;
}tRecord;

/*
Recibe una letra y devuelve el tipo enumerado correspondiente.
*/
tColores charToColor(char color);	 
/*
Recibe un tipo enumerado y devuelve el color correspondiente.
*/
tColores intToColor(int numero);	
/*
Genera una secuencia de numColores aleatoria, almacenándola en el array secuenciaColores.
*/
void generarSecuencia(tSecuencia secuenciaColores, int numColores);	
/*
Comprueba si el color introducido es correcto.
*/
bool comprobarColor(const tSecuencia secuenciaColores, int indice, tColores color);	
/*
Muestra la secuencia actual por pantalla.
*/
void mostrarSecuencia(const tSecuencia secuenciaColores, int numero);
/*
Controla el flujo de ejecución del juego.
*/
float comenzarJuego(string nombre, tModo modo, int ayudas);	
/*
Muestra el color de la secuencia por cout.
*/
void mostrarColor(tColores color);	
/*
Se encarga de comprobar si se puede, o no, ayudar al usuario.
*/
bool utilizarAyuda(const tSecuencia secuenciaColores, int indice, int &numAyudas);	
/*
Función que nos proporciona el menu de opciones.
*/
int menu();	
/*
Hace las comprobaciones para determinar el resultado de cada secuencia.
*/
bool comprobarSecuencia(int indice, bool fallo);	
/*
Carga, en tArray, los datos del fichero top.txt. 
Si no existe, tArray quedará vacío.
*/
void cargarRanking(tRecord &jugadores);	 
/*
Escribe en top.txt los datos del array tArray (vector de la estructura).
*/
void escribirRanking(const tRecord &jugadores);	
/*
Permite visualizar las 10 primeras posiciones del vector de estructura(o sea, los 10 mejores jugadores).
*/
void visualizarRanking(const tRecord &jugadores); 
/*
Permite visualizar el mejor jugador o los 'n' (n <= 10) mejores jugadores(si tienen la misma puntuación).
*/
void visualizarBestPlayer(const tRecord &jugadores); 
/*
Función que ordena nuestro array en función de la puntuación de los jugadores.
*/
void ordenarRanking(tRecord &jugadores);
/*
Inserta un nuevo jugador en el vector de jugadores.
*/
void insertarJugadorNuevo(tRecord &jugadores, string nombre);  


int main(){

	srand(time(NULL));
	tRecord jugadores;
	string nombre;
	tModo modo;
	float puntos = 0;
	cargarRanking(jugadores); // Cargamos lo que haya en top.txt en nuestro vector de jugadores

	cout << "Bienvenido a Simon Dice!" << endl << "Como te llamas? ";
	cin >> nombre;
	cout << "Hola " << nombre << ". " << endl;
	insertarJugadorNuevo(jugadores, nombre); // Aunque el jugador no llegue a jugar, se inserta su nombre y su puntuación se inicializa a 0

	int opcion = menu();
	while (opcion != 0) {
		switch (opcion){
		case 1:
			modo = Facil;
			puntos = comenzarJuego(nombre, modo, AYUDAS); // Insertar puntuación obtenida donde diga 'cont'
			if (puntos > jugadores.vector[jugadores.cont].puntuacion) // Si la puntuación objetina es mayor que la de alguna partida anterior...
				jugadores.vector[jugadores.cont].puntuacion = puntos; // Actualizamos la puntuación
			break;
		case 2:
			modo = Dificil;
			puntos = comenzarJuego(nombre, modo, AYUDAS); // Insertar puntuación obtenida donde diga 'cont'
			if (puntos > jugadores.vector[jugadores.cont].puntuacion) // Si la puntuación objetina es mayor que la de alguna partida anterior...
				jugadores.vector[jugadores.cont].puntuacion = puntos; // Actualizamos la puntuación
			break;
		case 3:
			ordenarRanking(jugadores);
			visualizarRanking(jugadores);
			break;
		case 4:
			ordenarRanking(jugadores);
			visualizarBestPlayer(jugadores);
			break;
		}
		opcion = menu();
	}
	ordenarRanking(jugadores); // Antes de finalizar el programa, ordenamos el vector
	escribirRanking(jugadores); // Y actualizamos el fichero top.txt
	cout << "El juego ha terminado." << endl;
	system("PAUSE");

	return 0;
}


int menu(){

	// IMPORTANTE: no se ha considerado qué ocurre si el usuario introduce caracteres que no sean numéricos
	int opcion;
	do {
		cout << "Elige una opcion para continuar: " << endl;
		cout << "0 - Salir." << endl;
		cout << "1 - Jugar en modo facil." << endl;
		cout << "2 - Jugar en modo dificil." << endl;
		cout << "3 - Ver 10 mejores jugadores." << endl;
		cout << "4 - Ver jugador(es) con la puntuacion mas alta." << endl;
		cout << "Opcion: ";
		cin >> opcion;
		if ((opcion < 0) || (opcion > 4)) {
			cout << "Opcion no valida!" << endl;
		}
	} while ((opcion < 0) || (opcion > 4));

	return opcion;
}


float comenzarJuego(string nombre, tModo modo, int ayudas){

	tColores colorElegido;
	tSecuencia vectorColores;
	char letraElegida;
	bool fallo = false, ayuda = false;
	float puntos = 0.0;
	int numAyudas = ayudas;	// Hay que usar una variable porque la constante AYUDAS no puede ser modificada

	if (modo == Facil) // En función del modo elegido, se generará una secuencia con un número de colores diferente (4 para fácil y 7 para difícil)
		generarSecuencia(vectorColores, MAX_COLORES_FACIL);
	else
		generarSecuencia(vectorColores, MAX_COLORES_DIFICIL);

	int j = 3;
	while (j <= MAX_COLORES_SEQ && fallo == false){	// Bucle que termina cuando has acertado todas las secuencias o cuando has fallado un color
		cout << "Secuencia numero " << j - 2 << ":  ";

		for (int k = 0; k < j; k++){ // Bucle para mostrar la secuencia actual que has de memorizar
			mostrarColor(vectorColores[k]);
			cout << "  ";
		}

		cout << endl << "Memoriza la secuencia." << endl;
		system("PAUSE");
		system("cls");
		cout << nombre << ", introduce la secuencia de " << j << " colores: " << endl;

		int i = 0;
		while (i < j && fallo == false){ // Bucle que termina cuando has acertado la secuencia actual o cuando has fallado un color
			cin >> letraElegida; // Recogemos la letra elegida

			while ((letraElegida < 65 || letraElegida > 122) || (letraElegida > 90 && letraElegida < 97)){	/// NOTA: Hay que intentar cambiar esto. Esta comprobación me parece muy antiestética
				cout << "Caracter incorrecto. Introduzca una letra valida: " << endl;
				cin >> letraElegida;
			}

			if (toupper(letraElegida) == 'X'){ // Si la letra es una 'X', entonces utilizamos la ayuda
				ayuda = utilizarAyuda(vectorColores, i, numAyudas);
				if (ayuda == true) { // Sólo incrementamos el valor de 'i' si la ayuda ha tenido éxito
					puntos = puntos - 7; // Y restamos 7 puntos por haber usado la ayuda (nótese que no sumamos los 5 por haber acertado el color)
					if (puntos < 0)	// Si los puntos son negativos, simplemente ponemos un 0
						puntos = 0;
					i++;
				}
			}
			else{
				colorElegido = charToColor(toupper(letraElegida)); // La transformamos en un color (asegurándonos que la letra es mayúscula)
				fallo = comprobarColor(vectorColores, i, colorElegido);	// Y comprobamos si coincide con la posición en el vectorColores
				if (fallo == false){ // Sólo incrementamos el valor de 'i' si hemos acertado el color
					puntos = puntos + 5;
					i++;
				}
				else{
					cin.sync(); // Si fallamos, descartamos el resto de carácteres. NOTA: ¡por esto entraba en un bucle infinito!
				}
			}
		}
		if (comprobarSecuencia(j, fallo) == true) // Sólo incrementamos el valor de 'j' si la secuencia es correcta
			puntos = puntos + 10;
		j++;
	}
	if (modo == Dificil) // Si estamos en el modo Difícil, multiplicamos por 1,5
		puntos = puntos * 1.5;

	return puntos;
}


tColores charToColor(char color){
	switch (color){
	case 'R':
		return Rojo; break;
	case 'V':
		return Verde; break;
	case 'A':
		return Azul; break;
	case 'D':
		return Dorado; break;
	case 'B':
		return Blanco; break;
	case 'M':
		return Marron; break;
	case 'N':
		return Naranja; break;
	default:
		break;
	}
}


tColores intToColor(int numero){
	switch (numero){
	case 0:
		return Rojo; break;
	case 1:
		return Verde; break;
	case 2:
		return Azul; break;
	case 3:
		return Dorado; break;
	case 4:
		return Blanco; break;
	case 5:
		return Marron; break;
	case 6:
		return Naranja; break;
	default:
		break;
	}
}

// IMPORTANTE: A esta función se le ha quitado el parámetro "tModo modo" puesto que no es necesario (lo único que le importa es saber el número de colores que le llegan para generar una secuencia u otra)
void generarSecuencia(tSecuencia secuenciaColores, int numColores){

	tColores colorGenerado;

	for (int i = 0; i < MAX_COLORES_SEQ; i++){
		colorGenerado = intToColor(rand() % (numColores + 1)); // Generamos el color dentro del conjunto
		secuenciaColores[i] = colorGenerado; // Rellenamos el vector de colores con el colorGenerado
	}
}


void mostrarColor(tColores color){
	if (color == Rojo) cout << "Rojo";
	else if (color == Verde) cout << "Verde";
	else if (color == Azul) cout << "Azul";
	else if (color == Dorado) cout << "Dorado";
	else if (color == Blanco) cout << "Blanco";
	else if (color == Marron) cout << "Marron";
	else if (color == Naranja) cout << "Naranja";
}


bool comprobarColor(const tSecuencia secuenciaColores, int indice, tColores color){

	if (secuenciaColores[indice] == color){	// Si el color almacenado en el vectorColores coincide con el color introducido, entonces fallo = false
		return false;
	}
	return true; // Si no coincide, entonces fallo = true
}


bool utilizarAyuda(const tSecuencia secuenciaColores, int indice, int &numAyudas){
	if (numAyudas == 0){
		cout << "Lo siento, no quedan ayudas disponibles. Debes acertar los colores restantes sin ayuda." << endl;
		return false;
	}
	else{
		numAyudas--;
		cout << "El siguiente color es el "; mostrarColor(secuenciaColores[indice]); cout << ". Te quedan " << numAyudas << " ayudas." << endl;
		return true;
	}
}


bool comprobarSecuencia(int indice, bool fallo){
	bool puntosSecuencia = false;

	if (fallo == true){
		cout << "Lo siento, has perdido." << endl;
		puntosSecuencia = false;
	}
	else if (fallo == false && indice == MAX_COLORES_SEQ){
		cout << "Has ganado el juego!!!" << endl;
		puntosSecuencia = true;
	}
	else if (fallo == false){
		cout << "Enhorabuena, has acertado la secuencia numero " << indice - 2 << endl;
		puntosSecuencia = true;
	}
	return puntosSecuencia;
}


void cargarRanking(tRecord &jugadores){

	ifstream archivo;
	float puntuacion;
	string nombre;
	jugadores.cont = 0; // Inicializamos el 'cont'

	archivo.open("top.txt");

	if (!archivo.is_open())
		cout << "No existe fichero, fichero creado" << endl;
	else {
		archivo >> puntuacion;
		archivo >> nombre;
		while (!archivo.eof() && jugadores.cont < MAX_JUGADORES){ // Mientras no lleguemos a EOF y aún queden jugadores por leer...
			jugadores.vector[jugadores.cont].puntuacion = puntuacion; // Introducimos la puntuación del jugador
			jugadores.vector[jugadores.cont].nombre = nombre;
			archivo >> puntuacion;
			archivo >> nombre;
			if (jugadores.cont != MAX_JUGADORES - 1) // Si no pusieramos esta condición, 'cont' valdría 10 cuando el vector está lleno (¡y sólo puede valer hasta 9!)
				jugadores.cont++;
		}
	}
	archivo.close();
}


void escribirRanking(const tRecord &jugadores){
	ofstream archivo;

	archivo.open("top.txt");
	for (int i = 0; i <= jugadores.cont; i++){ // Rellenamos el fichero recorriendo el vector desde 0 hasta la posición que marque 'cont'
		if (i != MAX_JUGADORES){
			archivo << jugadores.vector[i].puntuacion << " ";
			archivo << jugadores.vector[i].nombre << endl;
		}
	}
	archivo.close();
}


void visualizarRanking(const tRecord &jugadores){
	int i = 0;
	cout << " --------------> TOP 10 JUGADORES <--------------" << endl;
	do { // Conviene usar un do-While pues, al menos, mostraremos al primer jugador de todos
		i++;
		cout << jugadores.vector[i - 1].puntuacion << " ";
		cout << jugadores.vector[i - 1].nombre << endl;
	} while (i <= jugadores.cont);
}


void visualizarBestPlayer(const tRecord &jugadores){
	int i = 0;
	cout << " --------------> THE BEST PLAYER(S) <--------------" << endl;
	do { // Conviene usar un do-While pues, al menos, mostraremos al mejor de todos ellos
		i++;
		cout << jugadores.vector[i - 1].puntuacion << " ";
		cout << jugadores.vector[i - 1].nombre << endl;
	} while (i <= jugadores.cont && jugadores.vector[i].puntuacion == jugadores.vector[i - 1].puntuacion); // Mientras no superemos 'cont' y la puntuación del jugador n+1 sea igual que la del n... (mayor no será, pues está ordenado el vector)
}


void ordenarRanking(tRecord &jugadores){ // Para mantener ordenado el array usaremos el método de la burbuja

	int tempPuntuacion;
	string tempNombre;

	for (int i = 0; i <= jugadores.cont - 1; i++){
		for (int j = i + 1; j <= jugadores.cont; j++){
			if (jugadores.vector[j].puntuacion > jugadores.vector[i].puntuacion){
				tempPuntuacion = jugadores.vector[j].puntuacion; // Almacenamos en una variable auxiliar
				tempNombre = jugadores.vector[j].nombre;
				jugadores.vector[j].puntuacion = jugadores.vector[i].puntuacion; // Colocamos el valor correctamente en el vector
				jugadores.vector[j].nombre = jugadores.vector[i].nombre;
				jugadores.vector[i].puntuacion = tempPuntuacion; // Volvemos a restaurar el valor que había almacenado en 'temp'
				jugadores.vector[i].nombre = tempNombre;
			}
		}
	}
}


void insertarJugadorNuevo(tRecord &jugadores, string nombre){
	if (jugadores.cont < 10){ // Si hay menos de 10 jugadores, directamente se inserta en el lugar que indique 'cont'
		jugadores.vector[jugadores.cont].puntuacion = 0;
		jugadores.vector[jugadores.cont].nombre = nombre;
	}
	else{ // Si hay 10 jugadores, sacamos el último de todos e insertamos el nuevo jugador
		jugadores.vector[MAX_JUGADORES - 1].puntuacion = 0;
		jugadores.vector[MAX_JUGADORES - 1].nombre = nombre;
	}
}
