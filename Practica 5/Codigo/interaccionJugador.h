#ifndef INTERACCIONJUGADOR_H
#define INTERACCIONJUGADOR_H

#include "listaEdificios.h"
#include "listaJugadores.h"
#include "clasificacion.h"

namespace jugador
{
	/**
	* name: menu.
	* description: muestra por pantalla las opciones del menú, y pide la opcion.
	* arguments: nombre del jugador para mostrarlo.
	* return: int, opcion elegida.
	*/
	int menu(const tCadena jugador);

	/**
	* name: control.
	* description: llama a las funciones pertinentes, mostrando los errores que se puedan producir en su ejecución.
	* arguments:
			- int: opcion, entrada de la opcion seleccionada, define que subprogramas llamar.
			- tListaEdificios: edificios, lista de edificios, para los subpprogramas llamados por control.
			- tListaJugadores: jugadores, lista de jugadores, para los subpprogramas llamados por control.
			- int: indiceJugadorActivo, para saber con que jugador se está trabajando.
	*/
	void control(int opcion, tListaEdificios &edificios, tListaJugadores &jugadores, int indiceJugadorActivo);

	/**
	* name: misEdificios.
	* description: muestra la lista de edificios de jugador.
	* arguments:
			- tListaEdificios: edificios, lista de edificios a mostrar.
			- tjugador: jugador, para mostrar los datos de ese jugador.
	*/
	void misEdificios(tListaEdificios edificios, tJugador jugador);	

	/**
	* name: verEdificios.
	* description: muestra de la lista de edificios aquellos disponibles pasada como parámetro.
	* arguments:
			- tListaEdificios: edificios, lista de edificios a mostrar.
	*/
	void verEdificios(tListaEdificios edificios);

	/**
	* name: comprarEdificio.
	* description: pide al jugador el código de un edificio y, si procede (existe y disponible) lo marca como comprado y lo incluye en su lista de comprados.
	* arguments:
			- tListaEdificios: edificios, lista de edificios en la que marcar el edificio comprado.
			- tJugador: jugador, jugador que está comprando.
	*/
	void comprarEdificio(tListaEdificios &edificios, tJugador &jugador);
}

#endif