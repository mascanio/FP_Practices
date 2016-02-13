#ifndef JUGADORES_H
#define JUGADORES_H

#include "listaEdificios.h"

const int MAX_EDIFICIOS_COMPRADOS = 50;

typedef int tListaComprados[MAX_EDIFICIOS_COMPRADOS];

typedef struct {
	int contador;
	tListaComprados lista;
} tArrayComprados;

typedef struct{
	tCadena usuario;
	tCadena clave;
	tCadena universidad;
	int dinero;
	int prestigio;
	tArrayComprados comprados;
} tJugador;

const int SIZE_tJugador = sizeof(tJugador);

typedef tJugador *tPtrJugador;

/**
 * name: mostrarJugador
 * description: muestra los datos del jugador que queramos y sus edificios si los tiene.
 * arguments:
		- tListaEdificios: listaEdificios; para los edificios del jugador.
		- tJugador: jugador; jugador a mostrar.
*/
void mostrarJugador(tListaEdificios listaEdificios, tJugador jugador);

#endif