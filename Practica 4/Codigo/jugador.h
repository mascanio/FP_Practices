#ifndef JUGADORES_H
#define JUGADORES_H

#include "listaEdificios.h"

typedef int tListaComprados[MAX_EDIFICIOS];

typedef struct 
{
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

/**
 * name: mostrarJugador
 * description: muestra los datos del jugador que queramos y sus edificios si los tiene.
 * arguments:
		- tListaEdificios: edificios; estructura con contador de edificios y la lista de los edificios.
		- tJugador: jugador; los datos de la lista de edificios.
*/
void mostrarJugador(tListaEdificios edificios, tJugador jugador);

#endif