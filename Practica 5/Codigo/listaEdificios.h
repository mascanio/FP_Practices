#ifndef LISTAEDIFICIOS_H
#define LISTAEDIFICIOS_H

#include "edificio.h"

const int TAM_INICIO_EDIFICIOS = 10;

typedef struct{
	int contador;
	int contadorMax;
	tPtrEdificio lista; //Ptr a lista
} tListaEdificios;

//Funciones

/**
 * name: buscarEdificio.
 * description: dado el codigo del edificio, lo buscamos con binaria recursiva en la lista.
 * arguments:
		- tListaJugadores: listaEdificios; la lista de los edificios.
		- int: busacdo; codigo del edificio que buscamos.
		- int: ini; posicion de inicio de la búsqueda.
		- int: fin; posicion final de la búqueda.
		- int: pos; posicion del edificio que buscamos.
 * return: bool: encontrado; nos dice si se ha encontrado el edificio. true -> encontrado.
*/
bool buscarEdificio(tListaEdificios listaEdificios, int buscado, int ini, int fin, int &pos);

/**
 * name: insertarEdificio.
 * description: inserta el edificio nuevo en la lista.
 * arguments:
		- tListaEdificios: listaEdificios; estructura con la lista de edificios.
		- tEdificio: nuevoEdificio; el nuevo edificio que queremos inserta.
 * return: bool: salida; nos dice si el codigo duplicado (y no se ha podido insertar). true -> todo ha ido bien.
*/
bool insertarEdificio(tListaEdificios &listaEdificios, tEdificio nuevoEdificio);

/**
 * name: bajaEdificio.
 * description: marca el edificio (correspondiente al codigo) de la lista edificios como borrado.
 * arguments:
		- tListaEdificios: listaEdificios; estructura con la lista de edificios.
		- int: codigo; codigo del edificios que queremos marcar como borrado.
 * return: bool: salida; nos dice si se ha marcado como borrado (si existe y disponible). true -> marcado como borrado.
*/
bool bajaEdificio(tListaEdificios &listaEdificios, int codigo);

/**
 * name: inicializa.
 * description: inicializa la lista de edificios (contador a 0, contadorMax a tamaño inicial y punetro lista apuntando al espacio que se reserva en el heap).
 * arguments:
		- tListaEdificios: listaEdificios; lista a inicializar.
*/
void inicializa(tListaEdificios &listaEdificios);

/**

 * name: aumenta
 * description: aumenta el tamaño de la lista, actualiza contadorMax y reserva un espacio del mismo tamaño según la formula
			((tamActual * 3) / 2) + 1;
		y localiza la lista en la nueva posición reservada (puntero actualizado dentro).
 * arguments:
		- tListaEdificios: listaEdificios; lista a aumentar tamaño.
*/
void aumenta(tListaEdificios &listaEdificios);

#endif