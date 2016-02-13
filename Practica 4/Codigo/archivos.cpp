#include "archivos.h"

#include <fstream>
using namespace std;

#include <cstring>

////////////////////
// *** CARGAR *** //
////////////////////

bool cargar(tListaEdificios& listaEdificios){
	bool salida = false;
	int i = 0, aux;

	ifstream archivo;
	archivo.open(ARCHIVO_EDIFICIOS);

	if (archivo.is_open()){
		salida = true; //Apertura ok

		archivo >> aux; //Ya que puede estar vacío
		//Mientras no lea centinela y no llene la lista
		while ((aux != CENTINELA_EDIFICIOS) && (i < MAX_EDIFICIOS)){
			listaEdificios.lista[i].codigo = aux; //Aux no es el centinela -> es el código del sig edificio
			archivo.get();
			archivo.getline(listaEdificios.lista[i].nombre, TAM_CADENA);
			archivo >> listaEdificios.lista[i].precio;
			archivo >> listaEdificios.lista[i].dinero;
			archivo >> listaEdificios.lista[i].prestigio;
			archivo >> aux;
			listaEdificios.lista[i].estado = tEstado(aux);

			archivo >> aux; //Leo siguiente (o centinela o código del siguiente edificio)

			i++;
		}
		listaEdificios.contador = i;
		archivo.close();
	}

	return salida;
}
bool cargar(tListaJugadores& listaJugadores){
	bool salida = false;
	int i = 0, j = 0;
	tCadena aux;
	int intAux;

	ifstream archivo;
	archivo.open(ARCHIVO_JUGADORES);

	if (archivo.is_open()){
		salida = true; //Apertura ok

		archivo.getline(aux, TAM_CADENA); //Ya que puede estar vacío
		//Mientras no lea centinela y no llene la lista
		while ((strcmp(aux, CENTINELA_JUGADORES) != 0) && (i < MAX_JUGADORES)){
			strcpy_s(listaJugadores.lista[i].usuario, aux); //strcpy en visual 2012 da error de compilación, no warning
			archivo.getline(listaJugadores.lista[i].clave, TAM_CADENA);
			archivo.getline(listaJugadores.lista[i].universidad, TAM_CADENA);
			archivo >> listaJugadores.lista[i].dinero;
			archivo >> listaJugadores.lista[i].prestigio;

			//Bucle lectura edificios comprados
			j = 0;
			archivo >> intAux; //Puede no tener edificios
			//Mientras no lea centinela y no llene la lista de edificios comprados
			while ((intAux!= CENTINELA_EDIFICIOS) && (j < MAX_EDIFICIOS)){
				listaJugadores.lista[i].comprados.lista[j] = intAux;
				archivo >> intAux;

				j++;
			}
			listaJugadores.lista[i].comprados.contador = j;

			archivo.get();
			archivo.getline(aux, TAM_CADENA); //Leo siguiente (o centinela o nombre del siguiente jugador)

			i++;
		}
		listaJugadores.contador = i;
		archivo.close();
	}

	return salida;
}

/////////////////////
// *** GUARDAR *** //
/////////////////////

bool guardar(tListaEdificios listaEdificios){
	bool salida = false;

	ofstream archivo;
	archivo.open(ARCHIVO_EDIFICIOS);

	if (archivo.is_open()){
		salida = true; //Apertura OK
		//Vuelco todo en orden hasta que recorra toda la lista (hasta el contador)
		for (int i = 0; i < listaEdificios.contador; i++){
			archivo << listaEdificios.lista[i].codigo << endl ;
			archivo << listaEdificios.lista[i].nombre << endl ;
			archivo << listaEdificios.lista[i].precio << endl ;
			archivo << listaEdificios.lista[i].dinero << endl ;
			archivo << listaEdificios.lista[i].prestigio << endl ;
			archivo << listaEdificios.lista[i].estado << endl ;
		}
		//Centinela de archivo
		archivo << CENTINELA_EDIFICIOS;
		archivo.close();
	}

	return salida;
}
bool guardar(tListaJugadores listaJugadores){
	bool salida = false;

	ofstream archivo;
	archivo.open(ARCHIVO_JUGADORES);

	if (archivo.is_open()){
		salida = true; //Apertura OK
		//Vuelco todo en orden hasta que recorra toda la lista (hasta el contador)
		for (int i = 0; i < listaJugadores.contador; i++){
			archivo << listaJugadores.lista[i].usuario << endl ;
			archivo << listaJugadores.lista[i].clave << endl ;
			archivo << listaJugadores.lista[i].universidad << endl ;
			archivo << listaJugadores.lista[i].dinero << endl ;
			archivo << listaJugadores.lista[i].prestigio << endl ;
			//Recorrer edificios comprados
			for (int j = 0; j < listaJugadores.lista[i].comprados.contador; j++){
				archivo << listaJugadores.lista[i].comprados.lista[j] << endl ;
			}
			//Centinela de Edificios Comprados
			archivo << CENTINELA_EDIFICIOS<< endl ;
		}
		//Centinela de archivo
		archivo << CENTINELA_JUGADORES;
		archivo.close();
	}
	return salida;
}