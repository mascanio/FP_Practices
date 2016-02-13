#include "interaccionJugador.h"

#include <iostream> 
using namespace std;
#include <iomanip>

namespace jugador{
	int menu(const tCadena jugador){
		int opcion;
		cout << endl ;
		cout << "Menú de juego" << endl ;
		cout << "================" << endl ;
		cout << "Bienvenido " << jugador << ", elije una opción:" << endl << endl ;
		cout << "1.- Ver mis edificios" << endl;
		cout << "2.- Ver los edificios disponibles" << endl;
		cout << "3.- Comprar un edificio" << endl;
		cout << "4.- Ver la clasificación (ordenada por dinero)" << endl;
		cout << "5.- Ver la clasificación (ordenada por prestigio)" << endl;
		cout << "0.- Cerrar la sesión" << endl;
		cout << "Opción: ";
		cin >> opcion;

		return opcion;
	}

	void control(int opcion, tListaEdificios &edificios, tListaJugadores &jugadores, int indiceJugadorActivo){
		tClasificacion clasif;

		switch (opcion){
		case 1: 
			misEdificios(edificios, jugadores.lista[indiceJugadorActivo]);

			break ;
		case 2:
			verEdificios(edificios); 

			break;
		case 3: 
			comprarEdificio(edificios, jugadores.lista[indiceJugadorActivo]);

			break ;
		case 4: 			
			clasificacion(clasif, jugadores, true);
			verClasificacion(clasif, jugadores, true); 

			break ;
		case 5: 			
			clasificacion(clasif, jugadores, false);
			verClasificacion(clasif, jugadores, false);

			break ;

		case 0: cout << "Fin del la sesión" << endl ; break;

		default: break;
		}
	}

	void misEdificios(tListaEdificios edificios, tJugador jugador){	
		int posEdificio;

		cout << "Tienes " << jugador.comprados.contador << (jugador.comprados.contador == 1 ? " edificio: " : " edificios: ") << endl;
		//Recorro la lista de comprados con los códigos de los edificios
		for(int i = 0; i < jugador.comprados.contador; i++){
			//Busco y muestro el edificio i de la lista de comprados, en la posición posEdificio de la lista de edificios
			buscarEdificio(edificios, jugador.comprados.lista[i], posEdificio);
			mostrarEdificio(edificios.lista[posEdificio]);
		}	
	}

	void verEdificios(tListaEdificios edificios){
		for (int i = 0; i < edificios.contador; i++)
			//Muestro sólo los disponibles
				if (edificios.lista[i].estado == disponible)
					mostrarEdificio(edificios.lista[i]);
	}

	void comprarEdificio(tListaEdificios &edificios, tJugador &jugador){
		int codigo, pos = -1;
		bool encontrado = false;

		cout << "Introduce el codigo del edificio: " ;
		cin >> codigo;
		encontrado = buscarEdificio(edificios, codigo, pos);

		if (!encontrado){
			cout << "ERROR: no es un edificio valido." << endl;
		}
		else if (edificios.lista[pos].estado != disponible){
			cout << "ERROR: el edificio no está disponile." << endl;
		}
		else if (edificios.lista[pos].precio > jugador.dinero)	{
			cout << "ERROR: no dispones de créditos suficientes para comprar el edificio." << endl;
		}
		else{
			edificios.lista[pos].estado = comprado;
			jugador.comprados.lista[jugador.comprados.contador] = codigo;
			jugador.comprados.contador++;
			jugador.dinero -= edificios.lista[pos].precio;
			cout << "Has comprado el edificio y has pagado " << edificios.lista[pos].precio << endl;
		}

	}
}
