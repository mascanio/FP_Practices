#ifndef EDIFICIO_H
#define EDIFICIO_H

#include "tCadena.h"

typedef enum tEstado {
	disponible, comprado, borrado,
};

typedef struct{
	int codigo;
	tCadena nombre;
	int precio;
	int dinero;
	int prestigio;
	tEstado estado;
} tEdificio;

/**
 * name: mostrarEdificio.
 * description: muestra los datos del edificio que queramos y su estado.
 * arguments:
		- tEdificio: edificio; estructura con con los datos de edificios.
		- bool: reducido; para mostrar los datos de manera reducida o no. implícito no reducido
*/
void mostrarEdificio(tEdificio edificio, bool reducido = false);

#endif