#ifndef LOGIN_H
#define LOGIN_H

#include "listaEdificios.h"
#include "listaJugadores.h"
#include "tCadena.h"

//Admin
const tCadena ADMIN_NOMBRE = "admin" ;
const tCadena ADMIN_CLAVE = "12345" ;

const int MAX_INTENTOS = 3; //Número max de intentos para introducir clave


typedef enum tSalidaLogIn {
	logSalir, logAdmin, logJugador,
};


/**
 * name: logIn.
 * description: pide y comprueba usuario y llama a compruebaClave.
 * arguments:
		- tListaJugadores: listaJugadores; estructura con la lista de jugadores
		- int: indice; posicion del jugador que esta entrando al programa. -1 -> no existe; -2 -> admin; otro -> jugador.
 * return: bool: salida; nos dice si se han cargado los archivos. true -> cargado.
*/
tSalidaLogIn logIn(tListaJugadores listaJugadores, int &indice);

/**
 * name: compruebaClave.
 * description: comprueba si la clave solicitada en la función es la mism aque la del parámetro en MAX_INTENTOS.
 * arguments:
		- tCadena clave, clave que se va a comparar con la pedida
 * return: bool: claveOk; saber si la clave es la correcta o no. 
*/
bool compruebaClave(const tCadena clave);

#endif