#ifndef CLASIFICACION_H
#define CLASIFICACION_H

#include "listaJugadores.h"

//Tipo para la clasificaci�n, puntero a array dinamico que guarda en orden el �ndice de los jugadores
typedef int *tPtrClasificacion;

/**
* name: cmp.
* description: compara las dos estructuras jugador, por dinero o prestigio seg�n parametro, con >
* arguments:
		- tJugador: izq, der, jugadores a comparar **** izq > der ****
		- bool compararPorDinero, compara por dinero si true, por prestigio si false
* return: bool, devuelve el resultado de izq > der deacuerdo a compararPorDinero
*/
bool cmp(tJugador izq, tJugador der, bool compararPorDinero);
/**
* name: clasificacion.
* description: genera el array de clasificaci�n, ordena en orden descendente los jugadores y guarda los indices de los mismos, correspondientes a la lista de jugadores
* arguments:
		- tPtrClasificacion: clasificacion, puntero a array dinamico que va a contener los indices de los jugadores, ordenados; que van a ser mostrados (el tama�o viene dado por jugadores.contador)
		- tListaJugadores: jugadores, lista de los jugadores
		- bool compararPorDinero, clasifica por dinero si true, por prestigio si false
*/
void clasificacion(tPtrClasificacion clasificacion, tListaJugadores listaJugadores, bool compararPorDinero);
/**
* name: verClasificacion.
* description: muestra el array de clasificaci�n
* arguments:
		- tPtrClasificacion: clasificacion, puntero a array dinamico que va a contener los indices de los jugadores, ordenados; que van a ser mostrados (el tama�o viene dado por jugadores.contador)
		- tListaJugadores: jugadores, lista de los jugadores
		- bool compararPorDinero, muetra clasificaci�n por dinero si true, por prestigio si false
*/
void verClasificacion(tPtrClasificacion clasificacion, tListaJugadores listaJugadores, bool compararPorDinero);

#endif