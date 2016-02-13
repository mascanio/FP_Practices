///////////////////////////
// PRÁCTICA 5            //
// MIGUEL ASCANIO GÓMEZ  //
// PABLO FERNANDEZ GRADO //
///////////////////////////

/*
*** MÓDULOS ***
* tCadena: contiene el tipo de cadena de caracteres al estilo de c.

* Archivos: contiene las funciones de carga y volcado de los archivos (tanto bin como txt).

* logIn: contiene las funciones de logueo.
+ En logIn.h están las constantes de la clave y el nombre del admin (este ultimo se usa en el módulo interaccion)

* Interacción(jugador y admin): contiene todas las entradas de datos del usuario por consola (excepto las del logIn) 
y algunas lógicas muy básicas (bucles de recorrido) para salida por consola.
+ El espacio de nombres admin corresponde a las funciones del administrador.
+ El espacio de nombres jugador corresponde a las funciones del jugador.

* Clasificacion: contiene las funciones de clasificacion.
+ Método de clasificación: crea un array dinámico de int con los códigos de los jugadores, de tamaño contador de lista jugadores, 
insertados de tal manera que los códigos queden en el array ordenados según el orden adecuado (inserción en lista ordenada).

* Jugador y Edificio: contienen las funciones de salida por consola para mostrar un edificio o jugador.
**NOTA** Se han incluido las funciones nuevoJugador y nuevoUsuario en el módulo Interaccion, para tener toda la entrada por consola en un mismo módulo.

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
* description: carga los archivos binarios (modulo archivos.h).
* arguments:
- tListaEdificios: edificios; estructura con la lista de edificios.
- tListaEdificios: jugadores; estructura con la lista de jugadores.
* return: bool: salida; salir, true si los dos archivos cargan.
*/
bool cargaTodo(tListaEdificios &edificios, tListaJugadores &jugadores);

//////////////////
// *** MAIN *** //
//////////////////

int main(){
	system ("chcp 1252");

	tListaEdificios listaEdificios;
	inicializa(listaEdificios);
	tListaJugadores listaJugadores;
	inicializa(listaJugadores);
	tSalidaLogIn salidaLogueo = logAdmin;

	int opcion, indiceJugadorActivo;

	//Cargamos listas
	if (cargaTodo(listaEdificios, listaJugadores)){
		cout << "Listas cargadas" << endl ;
	}
	else
	{
		cout << "Se ha producido un error al cargar las listas, empezamos con listas vacías" << endl ;
		listaJugadores.contador = 0;
		listaEdificios.contador = 0;
	}

	//Ejecutamos bucle del juego mienrtas no se tenga salir
	while (salidaLogueo != logSalir){
		//Ejecuto login 
		salidaLogueo = logIn(listaJugadores, indiceJugadorActivo);
		//Según lo que devuelva login
		switch (salidaLogueo){
		case logAdmin:
			using namespace admin;
			opcion = -1;

			while (opcion != 0){

				opcion = menu();
				control(opcion, listaEdificios, listaJugadores);
			}
			break;
		case logJugador:
			using namespace jugador;
			opcion = -1;

			while (opcion != 0){

				opcion = menu(listaJugadores.lista[indiceJugadorActivo].usuario);
				control(opcion, listaEdificios, listaJugadores, indiceJugadorActivo);
			}
			break;
		case logSalir: 
			//Guardar listas
			guardarBin(listaEdificios);
			guardarBin(listaJugadores);

			//Liberar dinámica...
			delete [] listaEdificios.lista;
			delete [] listaJugadores.lista;

			cout << endl << "Listas guardadas... " ;

			break;
		}
	}
	return 0;
}

///////////////////////
// *** FUNCIONES *** //
///////////////////////

bool cargaTodo(tListaEdificios &listaEdificios, tListaJugadores &listaJugadores){
	bool salida = false;

	if (cargarBin(listaEdificios)){
		if (cargarBin(listaJugadores)){
			salida = true;
		}
		else{
			cout << "Error de apertura del archivo " << ARCHIVO_JUGADORES_BIN << endl ;
		}
	}
	else{
		if (!cargarBin(listaJugadores)){
			cout << "Error de apertura del archivo " << ARCHIVO_JUGADORES_BIN << endl ;
		}
		cout << "Error de apertura del archivo " << ARCHIVO_EDIFICIOS_BIN << endl ;
	}
	//Aunque cargue uno, devuelvo false (no tiene lógica usar sólo uno)
	return salida;
}