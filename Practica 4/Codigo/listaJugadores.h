#ifndef LISTAJUGADORES_H
#define LISTAJUGADORES_H

#include "tCadena.h"
#include "jugador.h"

const int MAX_JUGADORES = 20;

typedef tJugador tArrayJugadores[MAX_JUGADORES];

typedef struct{
	int contador;
	tArrayJugadores lista;	
} tListaJugadores;

//Funciones

/**
 * name: buscarJugador.
 * description: busca un jugador en el vector.
 * arguments:
		- tListaJugadores: listaJugadores; estructura con la lista de jugadores.
		- tCadena: buscar; el nombre que queremos buscar en la lista.
 * return: int, posición del jugador buscada, -1 si no lo encuentra
*/
int buscarJugador(tListaJugadores listaJugadores, const tCadena buscar);

/**
 * name: bajaJugador.
 * description: Da de baja e, jugador seleccionado.
 * arguments:
		- tListaEdificios: listaEdificios; estructura con la lista de edificios.
		- tListaJugadores: listaJugadores; estructura con la lista de jugadores
		- tCadena: jugador; el jugador que queremos borrar.
 * return: bool: salida; true -> existe el jugador.
*/
bool bajaJugador(tListaEdificios &listaEdificios, tListaJugadores &listaJugadores, const tCadena jugador);

/**
 * name: insertarJugador.
 * description: Si la lista no esta llena mete el jugador en la estructura.
 * arguments:
		- tListaJugadores: jugadores; estructura con la lista de jugadores
		- tJugador: newPlayer; el jugador que queremos meter (nos lo da la func meteJugador();).
 * return: bool: salida; true -> si la lista no estaba llena y hemos podido meter el nuevo jugador.
*/
bool insertarJugador(tListaJugadores &jugadores, tJugador newPlayer);

#endif