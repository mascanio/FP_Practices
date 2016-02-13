#ifndef LISTAJUGADORES_H
#define LISTAJUGADORES_H

#include "tCadena.h"
#include "jugador.h"

const int TAM_INICIO_JUGADORES = 10;

typedef struct{
	int contador;
	int contadorMax;
	tPtrJugador lista; //Ptr a lista
} tListaJugadores;

//Funciones

/**
 * name: buscarJugador.
 * description: busca un jugador en el vector.
 * arguments:
		- tListaJugadores: listaJugadores; estructura con la lista de jugadores.
		- tCadena: buscar; el nombre que queremos buscar en la lista.
 * return: int, posición del jugador buscado, -1 si no lo encuentra.
*/
int buscarJugador(tListaJugadores listaJugadores, const tCadena buscar);

/**
 * name: bajaJugador.
 * description: da de baja el jugador seleccionado.
 * arguments:
		- tListaEdificios: listaEdificios; estructura con la lista de edificios.
		- tListaJugadores: listaJugadores; estructura con la lista de jugadores.
		- tCadena: jugador; el jugador que queremos borrar.
 * return: bool: salida; true -> existe el jugador y se ha borrado.
*/
bool bajaJugador(tListaEdificios &listaEdificios, tListaJugadores &listaJugadores, const tCadena jugador);

/**
 * name: insertarJugador.
 * description: insertar el jugador en la lista.
 * arguments:
		- tListaJugadores: listaJugadores; estructura con la lista de jugadores.
		- tJugador: newPlayer; el jugador que queremos insertar.
 * return: bool: salida; true -> si hemos podido insertar el nuevo jugador (si el jugador no existía previamente).
*/
bool insertarJugador(tListaJugadores &listaJugadores, tJugador newPlayer);

/**
 * name: inicializa.
 * description: inicializa la lista de jugadores (contador a 0, contador max a tamaño inicial y punetro lista apuntando al espacio que se reserva en el heap).
 * arguments:
		- tListaJugadores: listaJugadores; lista a inicializar.
*/
void inicializa(tListaJugadores &listaJugadores);

/**
 * name: aumenta
 * description: aumenta el tamaño de la lista, actualiza contadorMax y reserva un espacio del mismo tamaño según la formula
		(tamActual * 3) / 2 + 1;
		y localiza la lista en la nueva posición reservada (puntero actualizado dentro)
 * arguments:
		- tListaJugadores: listaJugadores; lista a aumentar tamaño
*/
void aumenta(tListaJugadores &listaJugadores);

#endif