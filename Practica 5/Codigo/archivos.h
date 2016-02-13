#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "tCadena.h"
#include "listaEdificios.h"
#include "listaJugadores.h"

#include <fstream>
using namespace std;

const int CENTINELA_EDIFICIOS = -1;
const tCadena CENTINELA_JUGADORES = "X";

//Nombres de Archivo txt
const tCadena ARCHIVO_EDIFICIOS_TXT = "edificios.txt" ;
const tCadena ARCHIVO_JUGADORES_TXT = "jugadores.txt" ;

//Nombres de Archivos binarios
const tCadena ARCHIVO_EDIFICIOS_BIN = "edificios.dat" ;
const tCadena ARCHIVO_JUGADORES_BIN = "jugadores.dat" ;

////////////////////////
// *** CARGAR TXT *** //
////////////////////////

/**
 * name: cargarTxt.
 * description: Función sobrecargada que lee los datos de los archivos txt en las listas pertintentes.
 * arguments: según proceda:
		- tListaEdificios: listaEdificios; la lista de edificios en la que se cargan los datos leidos.
		- tListaJugadores: listaJugadores; la lista de jugadores en la que se cargan los datos leidos.
		- std::ifstream: archivo, el archivo pasado para leerlo
*/
void cargarTxt(tListaEdificios &listaEdificios, ifstream& archivo);
void cargarTxt(tListaJugadores &listaJugadores, ifstream& archivo);


////////////////////////////
// *** CARGAR BINARIOS*** //
////////////////////////////

/**
 * name: cargarBin.
 * description: Función sobrecargada que lee los datos de los archivos binarios en las listas pertintentes.
 * arguments: según proceda:
		- tListaEdificios: listaEdificios; la lista de edificios en la que se cargan los datos leidos.
		- tListaJugadores: listaJugadores; la lista de jugadores en la que se cargan los datos leidos.
 * return: bool: salida; true -> carga correcta.
*/
bool cargarBin(tListaEdificios &listaEdificios);
bool cargarBin(tListaJugadores &listaJugadores);


//////////////////////////////
// *** GUARDAR BINARIOS *** //
//////////////////////////////

/*
 * name: guardar.
 * description: Funcion sobrecargada que guarda los datos de las listas en los archivos pertintentes.
 * arguments: según proceda.
		- tListaEdificios: listaEdificios; la lista de edificios.
		- tListaJugadores: listaJugadores; la lista de jugadores.
*/
void guardarBin(tListaEdificios listaEdificios);
void guardarBin(tListaJugadores listaJugadores);

#endif