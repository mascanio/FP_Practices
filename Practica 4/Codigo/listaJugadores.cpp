#include "listaJugadores.h"
#include <cstring>

int buscarJugador(tListaJugadores listaJugadores, const tCadena buscar){
	int pos = -1, i = 0;
	//compraramos si la lista esta vacia o el nombre es el del administrador
	//mientras no acabe la lista y no lo encuentre (pos = -1)
	while (i < listaJugadores.contador && pos == -1){
		//Si coincide el que estoy comprobando y el que busco, me quedo con la posición; si no, mantentengo el no encontrado (-1)
		pos = (strcmp(buscar, listaJugadores.lista[i].usuario) == 0 ? i : -1);
		i++;
	}
	return pos;
}

bool bajaJugador(tListaEdificios& listaEdificios, tListaJugadores& listaJugadores, const tCadena jugador)
{
	bool salida = false;
	int pos = buscarJugador(listaJugadores, jugador), posicionEdificio;
	//Si el jugador existe
	if (pos != -1)
	{
		salida = true;
		//Sus edificios pasan a disponible: recorro su lista de comprados y marco esos edificios como disponibles
		for (int i = 0; i < listaJugadores.lista[pos].comprados.contador; i++)
		{
			buscarEdificio(listaEdificios, listaJugadores.lista[pos].comprados.lista[i], posicionEdificio);
			listaEdificios.lista[posicionEdificio].estado = disponible;
		}
		listaJugadores.contador--;
		//Desplaza la lista
		for (int i = pos; i < listaJugadores.contador; i++)
			listaJugadores.lista[i] = listaJugadores.lista[i + 1]; 
	}
	return salida;
}

bool insertarJugador(tListaJugadores &jugadores, tJugador newPlayer){
	bool salida = true;
	int i = 0;
	//Lista llena?
	if (jugadores.contador < MAX_JUGADORES){
		//Duplicado?
		while (salida && (i < MAX_JUGADORES)) {
			if (strcmp (jugadores.lista[i].usuario, newPlayer.usuario) == 0)
				salida = false; //Duplicado: return false y salgo del while
			i++;
		}
		if (salida){ //Inserto al final
			jugadores.lista[jugadores.contador] = newPlayer;
			jugadores.contador++;
		}
	}
	else {
		//Lista llena
		salida = false;
	}
	return salida;
}