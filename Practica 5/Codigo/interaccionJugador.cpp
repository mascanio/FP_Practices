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
		tPtrClasificacion clasif = NULL;

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
		case 4: 	//Clasificaciones
		case 5: 			
			//Reservo espacio para la lista de clasificaciones
			clasif = new int[jugadores.contador];
			//Si la opcion es 4, se pasa true para clasificar por dinero, si es 5 por prestigio: (opcion == 4)true define clasificacion por dinero
			clasificacion(clasif, jugadores, opcion == 4);
			verClasificacion(clasif, jugadores, opcion == 4);
			//Libero la memoria
			delete [] clasif;
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
			buscarEdificio(edificios, jugador.comprados.lista[i], 0, edificios.contador - 1, posEdificio); //Siempre va a existir, no hace falta comprobar
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
		encontrado = buscarEdificio(edificios, codigo, 0, edificios.contador-1, pos);

		if (!encontrado){
			cout << "ERROR: no es un edificio valido." << endl;
		}
		else if (edificios.lista[pos].estado != disponible){
			cout << "ERROR: el edificio no está disponile." << endl;
		}
		else if (edificios.lista[pos].precio > jugador.dinero){
			cout << "ERROR: no dispones de créditos suficientes para comprar el edificio." << endl;
		}
		else if (jugador.comprados.contador == MAX_EDIFICIOS_COMPRADOS) {
			cout << "ERROR: no puedes comprar más edificios, alcanzaste el máximo de " << MAX_EDIFICIOS_COMPRADOS << "." << endl;
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
