#include "interaccionAdmin.h"

#include <iostream> 
using namespace std;
#include <iomanip>


namespace admin{
	int menu(){
		int opcion;
		cout << endl ;
		cout << "Menú de administración" << endl ;
		cout << "======================" << endl ;
		cout << "1.- Ver el listado de edificios" << endl;
		cout << "2.- Nuevo edificio" << endl;
		cout << "3.- Borrar un edificio" << endl;
		cout << "4.- Ver el listado de jugadores" << endl;
		cout << "5.- Nuevo jugador" << endl;
		cout << "6.- Borrar un jugador" << endl;
		cout << "7.- Ejecutar un turno" << endl;
		cout << "8.- Ver la clasificación" << endl;
		cout << "0.- Cerrar la sesión" << endl;
		cout << "Opción: ";
		cin >> opcion;

		return opcion;
	}

	void control(int opcion, tListaEdificios &edificios, tListaJugadores &jugadores){
		//Array de las clasificaciones
		tClasificacion clasif;
		tJugador nuevo;

		switch (opcion){
		case 1: 
			verEdificios(edificios); 

			break;
		case 2: 
			cout << (insertarEdificio(edificios, nuevoEdificio()) ? "Edificio insertado con éxito..." : "ERROR al insertar: La lista está llena o el código está duplicado") << endl ; 

			break;
		case 3:
			cout << (borrarEdificio(edificios) ? "Edificio borrado con éxito..." : "ERROR: El edificio no existe o no está disponible") << endl ; 

			break;
		case 4: 
			verJugadores(edificios, jugadores); 

			break;
		case 5:  
			nuevo = nuevojugador();
			//No permito jugadores admin, s o salir
			if ((strcmp(nuevo.usuario, ADMIN_NOMBRE) != 0) && (strcmp(nuevo.usuario, "salir") != 0) && (strcmp(nuevo.usuario, "s") != 0))   
			{
				cout << (insertarJugador(jugadores, nuevo) ? "Jugador insertado con éxito..." : "ERROR al insertar: La lista está llena o el usuario está duplicado") << endl ; 
			}
			else
			{
				cout << "Error: usuario no válido" << endl;
			}
			break;
		case 6: 
			cout << (borrarJugador(edificios, jugadores) ? "Jugador borrado con éxito..." : "ERROR: El jugador no existe") << endl ; 

			break;
		case 7: 
			ejecutarTurno(edificios, jugadores);

			break;
		case 8: 
			//True para clasificacion por dinero
			clasificacion(clasif, jugadores, true);
			verClasificacion(clasif, jugadores, true);

			break;

		case 0: cout << "Fin del la sesión" << endl ; break;
		default: break;

		}
	}

	void verEdificios(tListaEdificios edificios){
		for (int i = 0; i < edificios.contador; i++)
			mostrarEdificio(edificios.lista[i]);
	}

	void verJugadores(tListaEdificios edificios, tListaJugadores jugadores){
		for (int i = 0; i < jugadores.contador; i++)
			mostrarJugador(edificios, jugadores.lista[i]);
	}

	bool borrarEdificio(tListaEdificios &edificios)
	{
		int codigoEdificioBorrar;

		cout << "Código del edificio a borrar: ";
		cin >> codigoEdificioBorrar;
		//Ejecuto borrado y devuelvo resultado
		return bajaEdificio(edificios, codigoEdificioBorrar) ;

	}

	bool borrarJugador(tListaEdificios &edificios, tListaJugadores &jugadores)
	{
		tCadena jugadorBorrar;

		cout << "Introduzca nombre del jugador a borrar: " ;
		cin >> jugadorBorrar;
		//Ejecuto borrado y devuelvo resultado
		return bajaJugador(edificios, jugadores, jugadorBorrar);
	}

	void ejecutarTurno(tListaEdificios edificios, tListaJugadores &jugadores)
	{
		int posEdificio;
		//Recorrer jugadores
		for (int i = 0; i < jugadores.contador; i++)
		{
			cout << "Procesando jugador: " << jugadores.lista[i].universidad << endl ;
			//Recorrer edificios del jugador i
			for (int j = 0; j < jugadores.lista[i].comprados.contador; j++)
			{
				//Buscar edificio de código de la lista comprados en posicion j
				buscarEdificio(edificios, jugadores.lista[i].comprados.lista[j], posEdificio);
				//Sumar datos del edificio en la posición posEdificio (el buscado) de la lista edificios
				jugadores.lista[i].dinero += edificios.lista[posEdificio].dinero;
				jugadores.lista[i].prestigio += edificios.lista[posEdificio].prestigio;
				//Mostrar
				cout << right << setw (16) << "Edificio #" << j + 1 ;
				mostrarEdificio(edificios.lista[posEdificio], true);
			}
			cout << "=======================================" << endl ;
		}
	}

	tEdificio nuevoEdificio(){
		tEdificio salida;
		cin.sync();
		cout << "Indentificador: ";
		cin >> salida.codigo;
		cout << "Nombre del edificio: ";
		cin.sync();
		cin.getline(salida.nombre, TAM_CADENA);
		cout << "Precio de compra: ";
		cin >> salida.precio;
		cout << "Prestigio por turno: ";
		cin >> salida.prestigio;
		cout << "Dinero por turno: ";
		cin >> salida.dinero;
		salida.estado = disponible;
		return salida;
	}

	tJugador nuevojugador(){
		tJugador newPlayer;
		cin.sync();
		cout << "Introduce el usuario: ";
		cin.getline(newPlayer.usuario, TAM_CADENA);
		cout << "Introduce el password: ";
		cin.getline(newPlayer.clave, TAM_CADENA);
		cout << "Introduce el nombre de la empresa: ";
		cin.getline(newPlayer.universidad, TAM_CADENA);
		newPlayer.dinero = 3000;
		newPlayer.prestigio = 0;
		newPlayer.comprados.contador = 0;

		return newPlayer;
	}

}
