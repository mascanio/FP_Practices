#include "login.h"

#include <iostream>
using namespace std;

tSalidaLogIn logIn(tListaJugadores listaJugadores, int &indice){
	tSalidaLogIn salida;
	bool salirWhile = false;
	tCadena entrada;

	cout << endl << endl 
		<< "Bienvenido a Campus Ville" << endl 
		<< "=========================" << endl << endl 
		<< "Escribe 'salir' o 's' para cerrar el programa..." << endl ;

	while (!salirWhile){
		cout << "Usuario: " ;

		cin.sync();
		cin.getline(entrada, TAM_CADENA);
		//Si "s" o "salir"
		if ((strcmp (entrada, "s") == 0) || (strcmp (entrada, "salir") == 0)){
			salida = logSalir;
			salirWhile = true;
		}
		else if (strcmp (entrada, ADMIN_NOMBRE) == 0)
		{
			//Si admin logea, salgo del while y devuelvo logAdmin
			salida = logAdmin;
			salirWhile = compruebaClave(ADMIN_CLAVE);
		}
		else {
			indice = buscarJugador(listaJugadores, entrada);
			//Si existe (si no, se vuelve a pedir)
			if (indice != -1){
				//Si logea, salgo del while y devuelvo logJugador
				salirWhile = compruebaClave(listaJugadores.lista[indice].clave);
				salida = logJugador;
			}
		}
	}
	return salida;
}

bool compruebaClave(const tCadena clave){

	bool claveOK = false;
	int intentos = MAX_INTENTOS;
	tCadena entrada = "c";
	//Mientras no acierte la clave ni agote intentos
	while ((!claveOK) && (intentos > 0)){
		cout << "contraseña (" << intentos << " intentos): ";
		cin >> entrada;
		claveOK = (strcmp(entrada, clave) ==  0);
		intentos--;
	}

	return claveOK;
}
