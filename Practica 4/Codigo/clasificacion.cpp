#include "clasificacion.h"

#include <iostream> 
using namespace std;
#include <iomanip>

bool cmp(tJugador izq, tJugador der, bool compararPorDinero)
{
	//Si comparar dinero, comparo con campo .dinero, si no, con .prestigio
	return (compararPorDinero ? izq.dinero > der.dinero : izq.prestigio > der.prestigio);
}
void clasificacion(tClasificacion &clasificacion, tListaJugadores jugadores, bool compararPorDinero)
{
	int contadorClasificacion = 1, j;

	clasificacion[0] = 0;
	//Recorrer listaJugadores
	for (int i = 1; i < jugadores.contador; i++)
	{
		j = 0;
		//Busco posición hasta fin de lista (entonces el jugador va al final de clasif) y cmp (el jugador de la lista es menor que el de la clasif, no hay que insertarlo en esa posición)
		while ((j < contadorClasificacion) && (cmp(jugadores.lista[clasificacion[j]], jugadores.lista[i], compararPorDinero)))
			j++;
		//Desplazo
		for (int k = contadorClasificacion; k > j; k--)
			clasificacion[k] = clasificacion[k - 1];
		//Inserto
		clasificacion[j] = i;
		contadorClasificacion++;
	}
}

void verClasificacion(tClasificacion clasificacion, tListaJugadores jugadores, bool compararPorDinero)
{
	cout << "Posición  "<< (compararPorDinero ? "Dinero" : "Prest.") << "   Nombre" << endl 
		<< "========  ======   ======" << endl ;

	for (int i = 0; i < jugadores.contador; i++)
	{
		//Se evalúa si se tiene que mosrar el dinero o el prestigio
		cout << right << setw(6) << i + 1 << setw(10) << (compararPorDinero ? jugadores.lista[clasificacion[i]].dinero : jugadores.lista[clasificacion[i]].prestigio) 
			<< "   " << jugadores.lista[clasificacion[i]].universidad << endl ;
	}
}