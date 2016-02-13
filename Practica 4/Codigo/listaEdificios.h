#ifndef LISTAEDIFICIOS_H
#define LISTAEDIFICIOS_H

#include "edificio.h"

const int MAX_EDIFICIOS = 50;

typedef tEdificio tArrayEdificios[MAX_EDIFICIOS];

typedef struct{
	int contador;
	tArrayEdificios lista;	
} tListaEdificios;

//Funciones

/**
 * name: buscarEdificio.
 * description: dado el codigo del edificio, lo buscamos con binaria en la lista.
 * arguments:
		- tListaJugadores: lista; la lista de los edificios.
		- int: busacdo; codigo del edificio que buscamos.
		- int: pos; codigo del edificio que buscamos.
 * return: bool: encontrado; nos dice si se ha encontrado el edificio. true -> encontrado.
*/
bool buscarEdificio(tListaEdificios lista, int buscado, int &pos);

/**
 * name: insertarEdificio.
 * description: mete el edificio nuevo en la lista.
 * arguments:
		- tListaEdificios: lista; estructura con la lista de edificios.
		- tEdificio: nuevoEdificio; el nuevo edificio que queremos meter.
 * return: bool: salida; nos dice si la lista no esta llena o el codigo duplicado. true -> todo ha ido bien.
*/
bool insertarEdificio(tListaEdificios &lista, tEdificio nuevoEdificio);

/**
 * name: bajaEdificio.
 * description: marca el edificio (correspondiente al codigo) de la lista edificios como borrado
 * arguments:
		- tListaEdificios: edificios; estructura con la lista de edificios
		- int: codigo; codigo del edificios que queremos marcar como borrado.
 * return: bool: salida; nos dice si se ha marcado como borrado. true -> marcado como borrado.
*/
bool bajaEdificio(tListaEdificios &edificios, int codigo);

#endif