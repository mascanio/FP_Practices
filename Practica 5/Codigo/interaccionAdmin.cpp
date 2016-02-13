#include "interaccionAdmin.h"

#include <iostream> 
using namespace std;
#include <fstream>
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
		cout << "9.- Importar datos de archivos de texto" << endl;
		cout << "0.- Cerrar la sesión" << endl;
		cout << "Opción: ";
		cin >> opcion;

		return opcion;
	}

	void control(int opcion, tListaEdificios &listaEdificios, tListaJugadores &listaJugadores){

		switch (opcion){
		case 1: 
			verEdificios(listaEdificios); 

			break;
		case 2: 
			cout << (insertarEdificio(listaEdificios, nuevoEdificio()) ? "Edificio insertado con éxito..." : "ERROR al insertar: el código está duplicado") << endl ; 

			break;
		case 3:
			cout << (borrarEdificio(listaEdificios) ? "Edificio borrado con éxito..." : "ERROR: El edificio no existe o no está disponible") << endl ; 

			break;
		case 4: 
			verJugadores(listaEdificios, listaJugadores); 

			break;
		case 5:  
			{
				tJugador nuevo = nuevojugador();
				//No permito listaJugadores admin, s o salir
				if ((strcmp(nuevo.usuario, ADMIN_NOMBRE) != 0) && (strcmp(nuevo.usuario, "salir") != 0) && (strcmp(nuevo.usuario, "s") != 0)) {
					cout << (insertarJugador(listaJugadores, nuevo) ? "Jugador insertado con éxito..." : "ERROR al insertar: el usuario está duplicado") << endl ; 
				}
				else {
					cout << "Error: usuario no válido" << endl;
				}
				break;
			}
		case 6: 
			cout << (borrarJugador(listaEdificios, listaJugadores) ? "Jugador borrado con éxito..." : "ERROR: El jugador no existe") << endl ; 

			break;
		case 7: 
			ejecutarTurno(listaEdificios, listaJugadores);

			break;
		case 8: 
			{
				//Array de las clasificaciones
				//Reservo espacio para la lista de clasificaciones
				tPtrClasificacion clasif = new int[listaJugadores.contador];

				//True para clasificacion por dinero
				clasificacion(clasif, listaJugadores, true);
				verClasificacion(clasif, listaJugadores, true);
				//Libero la memoria
				delete [] clasif;

				break;
			}
		case 9:
			{
				ifstream archivoEd, archivoJug;
				archivoEd.open(ARCHIVO_EDIFICIOS_TXT);
				if (archivoEd.is_open())
				{
					archivoJug.open(ARCHIVO_JUGADORES_TXT);
					if (archivoJug.is_open())
					{
						listaEdificios.contador = 0; //Sobreescribo lo anterior
						cargarTxt(listaEdificios, archivoEd);
						archivoEd.close();
						listaJugadores.contador = 0; //Sobreescribo lo anterior
						cargarTxt(listaJugadores, archivoJug);
						archivoJug.close();
						cout << "Archivos de texto cargados con éxito" << endl ;
					}
					else
					{
						cout << "Error de apertura de: " << ARCHIVO_JUGADORES_TXT << endl ;
					}
				}
				else
				{
					cout << "Error de apertura de: " << ARCHIVO_EDIFICIOS_TXT << endl ;
				}

				break;
			}
		case 0: cout << "Fin del la sesión" << endl ; break;

		default: break;
		}
	}

	void verEdificios(tListaEdificios listaEdificios){
		for (int i = 0; i < listaEdificios.contador; i++)
			mostrarEdificio(listaEdificios.lista[i]);
	}

	void verJugadores(tListaEdificios listaEdificios, tListaJugadores listaJugadores){
		for (int i = 0; i < listaJugadores.contador; i++)
			mostrarJugador(listaEdificios, listaJugadores.lista[i]);
	}

	bool borrarEdificio(tListaEdificios &listaEdificios) {
		int codigoEdificioBorrar;

		cout << "Código del edificio a borrar: ";
		cin >> codigoEdificioBorrar;
		//Ejecuto borrado y devuelvo resultado
		return bajaEdificio(listaEdificios, codigoEdificioBorrar) ;
	}

	bool borrarJugador(tListaEdificios &listaEdificios, tListaJugadores &listaJugadores) {
		tCadena jugadorBorrar;

		cout << "Introduzca nombre del jugador a borrar: " ;
		cin >> jugadorBorrar;
		//Ejecuto borrado y devuelvo resultado
		return bajaJugador(listaEdificios, listaJugadores, jugadorBorrar);
	}

	void ejecutarTurno(tListaEdificios listaEdificios, tListaJugadores &listaJugadores)	{
		int posEdificio;
		//Recorrer listaJugadores
		for (int i = 0; i < listaJugadores.contador; i++)
		{
			cout << "Procesando jugador: " << listaJugadores.lista[i].universidad << endl ;
			//Recorrer listaEdificios del jugador i
			for (int j = 0; j < listaJugadores.lista[i].comprados.contador; j++)
			{
				//Buscar edificio de código de la lista comprados en posicion j
				buscarEdificio(listaEdificios, listaJugadores.lista[i].comprados.lista[j], 0, listaEdificios.contador -1, posEdificio);
				//Sumar datos del edificio en la posición posEdificio (el buscado) de la lista listaEdificios
				listaJugadores.lista[i].dinero += listaEdificios.lista[posEdificio].dinero;
				listaJugadores.lista[i].prestigio += listaEdificios.lista[posEdificio].prestigio;
				//Mostrar
				cout << right << setw (16) << "Edificio #" << j + 1 ;
				mostrarEdificio(listaEdificios.lista[posEdificio], true);
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
