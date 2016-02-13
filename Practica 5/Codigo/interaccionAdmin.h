#ifndef INTERACCIONADMIN_H
#define INTERACCIONADMIN_H

#include "listaEdificios.h"
#include "listaJugadores.h"
#include "login.h" //Para Nombre del admin (no permitir jugador con ese nombre)
#include "clasificacion.h"
#include "archivos.h" // para opcion importar datos del .txt

namespace admin
{
	/**
	* name: menu.
	* description: muestra por pantalla las opciones del menú, y pide la opcion.
	* return: int, opcion elegida.
	*/
	int menu();

	/**
	* name: control.
	* description: llama a las funciones pertinentes, mostrando los errores que se puedan producir en su ejecución.
	* arguments:
			- int: opcion, entrada de la opcion seleccionada, define que subprogramas llamar.
			- tListaEdificios: edificios, lista de edificios, para los subpprogramas llamados por control.
			- tListaJugadores: listaJugadores, lista de jugadores, para los subpprogramas llamados por control.
	*/
	void control(int opcion, tListaEdificios& listaEdificios, tListaJugadores& listaJugadores);

	/**
	* name: verEdificios.
	* description: muestra la lista de edificios pasada como parámetro.
	* arguments:
			- tListaEdificios: listaEdificios, lista de edificios a mostrar.
	*/
	void verEdificios(tListaEdificios listaEdificios);

	/**
	* name: verJugadores.
	* description: muestra la lista de jugadores pasada como parámetro.
	* arguments:
			- tListaJugadores: listaJugadores, lista de jugadores a mostrar.
			- tListaEdificios: listaEdificios, lista de edificios necesario para mostrar los edificios de cada jugador.
	*/
	void verJugadores(tListaEdificios listaEdificios, tListaJugadores listaJugadores);

	/**
	* name: borrarEdificio.
	* description: borra un edificio. Pide al admin el código del edificio a borrar.
	* arguments:
			- tListaEdificios listaEdificios, lista de edificios.
	* return: bool, true si el edificio existe y no está en uso.
	*/
	bool borrarEdificio(tListaEdificios &listaEdificios);
	
	/**
	* name: borrarJugador.
	* description: borra un jugador. Pide al admin el nombre del jugador a borrar. Actualiza estado de los edificios.
	* arguments:
			- tListaJugadores listaJugadores, lista de jugadores de la que se va a borrar el jugador.
			- tListaEdificios listaEdificios, lista de edificios para actualizar el estado de los edificios del jugador borrado.
	* return: bool, true si el jugador se ha borrado (existe).
	*/
	bool borrarJugador(tListaEdificios &listaEdificios, tListaJugadores &listaJugadores);
		
	/**
	* name: ejecutarTurno.
	* description: ejecuta un turno: suma a los campos dinero y prestigio los valores que generan por turnos
			los edificios que posea cada jugador.
	* arguments:
			- tListaJugadores listaJugadores, lista de jugadores (para modificar el prestigio y el dinero).
			- tListaEdificios listaEdificios, lista de edificios (para la info de los edificios).
	*/
	void ejecutarTurno(tListaEdificios listaEdificios, tListaJugadores &listaJugadores);
	
	/**
	* name: nuevoJugador, nuevoEdificio.
	* description: solicitan al usuario los datos del nuevo  edificio o jugador, y devuelve la estructura correspondiente.
	* return: tEdificio o tJugador, estructura con los datos introducidos.
	*/
	tEdificio nuevoEdificio();
	tJugador nuevojugador();

}

#endif