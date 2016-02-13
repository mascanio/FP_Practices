#include "listaJugadores.h"
#include <cstring>

int buscarJugador(tListaJugadores listaJugadores, const tCadena buscar){
	int pos = -1, i = 0;
	//compraramos si la lista esta vacia o el nombre es el del administrador
	//mientras no acabe la lista y no lo encuentre (pos = -1)
	while ((i < listaJugadores.contador) && (pos == -1)){
		//Si coincide el que estoy comprobando y el que busco, me quedo con la posición; si no, mantentengo el no encontrado (-1)
		pos = (strcmp(buscar, listaJugadores.lista[i].usuario) == 0 ? i : -1);
		i++;
	}
	return pos;
}

bool bajaJugador(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores, const tCadena jugador){
	bool salida = false;
	int pos = buscarJugador(listaJugadores, jugador), posicionEdificio;
	//Si el jugador existe
	if (pos != -1)
	{
		salida = true;
		//Sus edificios pasan a disponible: recorro su lista de comprados y marco esos edificios como disponibles
		for (int i = 0; i < listaJugadores.lista[pos].comprados.contador; i++)
		{
			buscarEdificio(listaEdificios, listaJugadores.lista[pos].comprados.lista[i], 0, listaEdificios.contador -1, posicionEdificio);
			listaEdificios.lista[posicionEdificio].estado = disponible;
		}
		listaJugadores.contador--;
		//Desplaza la lista
		for (int i = pos; i < listaJugadores.contador; i++)
			listaJugadores.lista[i] = listaJugadores.lista[i + 1]; 
	}
	return salida;
}

bool insertarJugador(tListaJugadores &listaJugadores, tJugador newPlayer){
	bool salida = true;
	int i = 0;

	//Duplicado?
	while (salida && (i < listaJugadores.contador)) {
		if (strcmp (listaJugadores.lista[i].usuario, newPlayer.usuario) == 0)
			salida = false; //Duplicado: return false y salgo del while
		i++;
	}
	if (salida){
		//Lista llena? aumento tamaño (sólo aumentar si se va a introducir uno nuevo)
		if (listaJugadores.contador == listaJugadores.contadorMax)
			aumenta(listaJugadores);
		//Inserto al final
		listaJugadores.lista[listaJugadores.contador] = newPlayer;
		listaJugadores.contador++;
	}
	return salida;
}

void inicializa(tListaJugadores &listaJugadores) {
	listaJugadores.contador = 0;
	listaJugadores.lista = new tJugador[TAM_INICIO_JUGADORES];
	listaJugadores.contadorMax = TAM_INICIO_JUGADORES;
}

void aumenta(tListaJugadores &listaJugadores) {
	//Nuevo tamaño maximo
	int maxAux = ((listaJugadores.contadorMax * 3) / 2) + 1;

	//Nuevo espacio en el heap
	tPtrJugador aux = new tJugador[maxAux];

	//Muevo del espacio viejo al nuevo
	for (int i = 0; i < listaJugadores.contador; i++)
		aux[i] = listaJugadores.lista[i] ;

	//Libero espacio viejo
	delete [] listaJugadores.lista;

	//Actualizo lista con lso datos nuevos
	listaJugadores.lista = aux;
	listaJugadores.contadorMax = maxAux;
}