#ifndef CLASIFICACION_H
#define CLASIFICACION_H

#include "listaJugadores.h"

//Tipo para la clasificación, para guardar en orden el índice de los jugadores
typedef int tClasificacion[MAX_JUGADORES];

/**
* name: cmp.
* description: compara las dos estructuras jugador, por dinero o prestigio según parametro, con >
* arguments:
		- tJugador: izq, der, jugadores a comparar **** izq > der ****
		- bool compararPorDinero, compara por dinero si true, por prestigio si false
* return: bool, devuelve el resultado de izq > der deacuerdo a compararPorDinero
*/
bool cmp(tJugador izq, tJugador der, bool compararPorDinero);
/**
* name: clasificacion.
* description: genera el array de clasificación, ordena en orden descendente los jugadores y guarda los indices de los mismos, correspondientes a la lista de jugadores
* arguments:
		- tClasificacion: clasificacion, array que va a contener los indices de los jugadores, ordenados
		- tListaJugadores: jugadores, lista de los jugadores
		- bool compararPorDinero, clasifica por dinero si true, por prestigio si false
*/
void clasificacion(tClasificacion &clasificacion, tListaJugadores jugadores, bool compararPorDinero);
/**
* name: verClasificacion.
* description: muestra el array de clasificación
* arguments:
		- tClasificacion: clasificacion, array que va a contener los indices de los jugadores, ordenados; que van a ser mostrados
		- tListaJugadores: jugadores, lista de los jugadores
		- bool compararPorDinero, muetra clasificación por dinero si true, por prestigio si false
*/
void verClasificacion(tClasificacion clasificacion, tListaJugadores jugadores, bool compararPorDinero);

#endif