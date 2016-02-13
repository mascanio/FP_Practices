#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "tCadena.h"
#include "listaEdificios.h"
#include "listaJugadores.h"

const int CENTINELA_EDIFICIOS = -1;
const tCadena CENTINELA_JUGADORES = "X";

//Nombres de Archivo
const tCadena ARCHIVO_EDIFICIOS = "edificios.txt" ;
const tCadena ARCHIVO_JUGADORES = "jugadores.txt" ;

////////////////////
// *** CARGAR *** //
////////////////////

/**
 * name: cargar.
 * description: Funcion sobrecargada que lee los datos de los archivos definidos en cadena.h en las listas pertintentes.
 * arguments: según proceda:
		- tListaEdificios: listaEdificios; la lista de edificios.
		- tListaJugadores: listaJugadores; la lista de jugadores.
 * return: bool: salida; true -> carga correcta.
*/
bool cargar(tListaEdificios &listaEdificios);
bool cargar(tListaJugadores &listaJugadores);

/////////////////////
// *** GUARDAR *** //
/////////////////////

/*
 * name: guardar.
 * description: Funcion sobrecargada que guarda los datos de las listas en los archivos definidos en cadena.h pertintentes.
 * arguments: según proceda.
		- tListaEdificios: listaEdificios; la lista de edificios.
		- tListaJugadores: listaJugadores; la lista de jugadores.
 * return: bool: salida; true -> si el archivo guarda.
*/
bool guardar(tListaEdificios listaEdificios);
bool guardar(tListaJugadores listaJugadores);

#endif