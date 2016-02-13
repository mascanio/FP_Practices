#include "jugador.h"

#include <iostream>
using namespace std;
#include <iomanip>

void mostrarJugador(tListaEdificios listaEdificios, tJugador jugador){
	bool encontrado = false;
	int position = 0;

	cout << "================================================== "	 << endl ;
	cout << right << setw (12) << "Usuario: " << left << jugador.usuario << endl ;
	cout << right << setw (12) << "Dinero: " << left << jugador.dinero << endl ;
	cout << right << setw (12) << "Prestigio: " << left << jugador.prestigio << endl ;
	cout << right << setw (12) << "Edificios: " << left << jugador.comprados.contador << endl ;

	//Mostrar lista de edificios	 
	for(int i = 0; i < jugador.comprados.contador; i++){
		//Busca el edificio
		buscarEdificio(listaEdificios, jugador.comprados.lista[i], 0, listaEdificios.contador - 1, position);
		//Lo muestra 
		cout << right << setw (16) << "Edificio #" << i + 1 ;
		mostrarEdificio(listaEdificios.lista[position], true);		
	}
}