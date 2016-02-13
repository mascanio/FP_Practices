///////////////////////////
// PRÁCTICA 4            //
// MIGUEL ASCANIO GÓMEZ  //
// PABLO FERNANDEZ GRADO //
///////////////////////////

/*
 *** MÓDULOS ***
	* tCadena: contiene el tipo de cadena de caracteres al estilo de c

	* Archivos: contiene las funciones de carga y volcado de los archivos

	* logIn: contiene las funciones de logueo
			+ En logIn.h están las constantes de la clave y el nombre del admin (este ultimo se usa en el módulo interaccion)

	* Interacción(jugador y admin): contiene todas las entradas de datos del usuario por consola (excepto las del logIn) 
						y algunas lógicas muy básicas (bucles de recorrido) para salida por consola
			+ El espacio de nombres admin corresponde a las funciones del administrador
			+ El espacio de nombres jugador corresponde a las funciones del jugador

	* Clasificacion: contiene las funciones de clasificacion.
			+ Método de clasificación: crea un array de int con los códigos de los jugadores, insertados de tal manera que los códigos queden en el array ordenados
												según el orden adecuado (inserción en lista ordenada)

	* Jugador y Edificio: contienen las funciones de salida por consola para mostrar un edificio o jugador
	**NOTA** Se han incluido las funciones nuevoJugador y nuevoUsuario en el módulo Interaccion, para tener tda la entrada por consola en un mismo módulo

	*listaJugadores y listaEdificios: contienen funciones de búsqueda, inserción y eliminación de elementos de la lista adecuada.
*/

#include <iostream>
using namespace std;

#include <cstring>

#include "edificio.h"
#include "jugador.h"
#include "listaEdificios.h"
#include "listaJugadores.h"
#include "tCadena.h"
#include "archivos.h"
#include "login.h"
#include "interaccionAdmin.h"
#include "interaccionJugador.h"
#include "clasificacion.h"


////////////////////////
// *** PROTOTIPOS *** //
////////////////////////

/**
 * name: cargaTodo.
 * description: carga los archivos (modulo archivos.h).
 * arguments:
		- tListaEdificios: edificios; estructura con la lista de edificios.
		- tListaEdificios: jugadores; estructura con la lista de jugadores.
 * return: bool: salida; salir, administrador o jugador.
*/
bool cargaTodo(tListaEdificios &edificios, tListaJugadores &jugadores);

//////////////////
// *** MAIN *** //
//////////////////

int main(){
	system ("chcp 1252");

	tListaEdificios edificios;
	tListaJugadores jugadores;
	tSalidaLogIn salidaLogueo = logAdmin;

	int opcion, indiceJugadorActivo;

	//Cargamos listas
	if (cargaTodo(edificios, jugadores)){
		cout << "Listas cargadas" << endl ;
	}
	else
	{
		cout << "Se ha producido un error al cargar las listas, empezamos con listas vacías" << endl ;
		jugadores.contador = 0;
		edificios.contador = 0;
	}
	//Ejecutamos bucle del juego
	while (salidaLogueo != logSalir){
		//Ejecuto login 
		salidaLogueo = logIn(jugadores, indiceJugadorActivo);
		//Según lo que devuelva login
		switch (salidaLogueo){
		case logAdmin:
			opcion = -1;

			while (opcion != 0){
				opcion = admin::menu();
				admin::control(opcion, edificios, jugadores);
			}
			break;

		case logJugador:
			opcion = -1;

			while (opcion != 0){
				opcion = jugador::menu(jugadores.lista[indiceJugadorActivo].usuario);
				jugador::control(opcion, edificios, jugadores, indiceJugadorActivo);
			}
			break;

		case logSalir: //Guardar listas
			guardar(edificios);
			guardar(jugadores);

			cout << "Listas guardadas... " ;

			break;
		}
	}
	return 0;
}

///////////////////////
// *** FUNCIONES *** //
///////////////////////

bool cargaTodo(tListaEdificios& edificios, tListaJugadores& jugadores){
	bool salida = false;

	if (cargar(edificios)){
		if (cargar(jugadores)){
			salida = true;
		}
		else{
			cout << "Error de apertura del archivo " << ARCHIVO_JUGADORES << endl ;
		}
	}
	else{
		if (!cargar(jugadores)){
			cout << "Error de apertura del archivo " << ARCHIVO_JUGADORES << endl ;
		}
		cout << "Error de apertura del archivo " << ARCHIVO_EDIFICIOS << endl ;
	}

	return salida;
}