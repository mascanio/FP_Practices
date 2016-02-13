#include "edificio.h"

#include <iostream>
using namespace std;
#include <iomanip>
#include "listaJugadores.h"

void mostrarEdificio(tEdificio edificio, bool reducido){

	if (!reducido)
	{

		cout << "================================================== "	 << endl ;
		cout << right << setw (24) << "Identificador: "			<< left << edificio.codigo << endl ;
		cout << right << setw (24) << "Nombre: "					<< left << edificio.nombre << endl ;
		cout << right << setw (24) << "Precio de compra: "		<< left << edificio.precio << endl ;
		cout << right << setw (24) << "Dinero por turno: "		<< left << edificio.dinero << endl ;
		cout << right << setw (24) << "Prestigio por turno: " << left << edificio.prestigio << endl ;

		cout << right << setw (24) << "Estado: " ;
		switch (edificio.estado){
		case disponible:	cout << left << "DISPONIBLE"	<< endl ; break ;
		case comprado:		cout << left << "COMPRADO"		<< endl ; break ;
		case borrado:		cout << left << "BORRADO"		<< endl ; break ;
		}
	}
	else
	{
		cout << " - "<< edificio.nombre << " - D:" << edificio.dinero << " - P:"<< edificio.prestigio << endl ;
	}
}