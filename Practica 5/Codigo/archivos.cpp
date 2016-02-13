#include "archivos.h"

////////////////////////
// *** CARGAR TXT *** //
////////////////////////

void cargarTxt(tListaEdificios &listaEdificios, ifstream& archivo){
	bool salida = false;
	int intAux;
	char descarte;

	tEdificio structAux;

	archivo >> structAux.codigo; //Ya que puede estar vacío
	//Mientras no lea centinela
	while (structAux.codigo != CENTINELA_EDIFICIOS){
		//Aux no es el centinela -> es el código del sig edificio
		archivo.get(descarte);
		archivo.getline(structAux.nombre, TAM_CADENA);
		archivo >> structAux.precio;
		archivo >> structAux.dinero;
		archivo >> structAux.prestigio;
		//Lectura de estado
		archivo >> intAux;
		structAux.estado = tEstado (intAux);
		//Vuelco el aux en la lista (antes compruebo tamaño y agrando lista si necesario)
		if (listaEdificios.contador == listaEdificios.contadorMax)
			aumenta(listaEdificios);

		listaEdificios.lista[listaEdificios.contador] = structAux;
		listaEdificios.contador++;

		archivo >> structAux.codigo; //Leo siguiente (o centinela o código del siguiente edificio)
	}
}
void cargarTxt(tListaJugadores &listaJugadores, ifstream& archivo){
	int i = 0, //Contador para lista de comprados 
		intAux;
	char descarte;

	tJugador structAux;


	archivo.getline(structAux.usuario, TAM_CADENA); //Ya que puede estar vacío
	//Mientras no lea centinela
	while (strcmp(structAux.usuario, CENTINELA_JUGADORES) != 0){
		archivo.getline(structAux.clave, TAM_CADENA);
		archivo.getline(structAux.universidad, TAM_CADENA);
		archivo >> structAux.dinero;
		archivo >> structAux.prestigio;

		//Bucle lectura edificios comprados
		i = 0;
		archivo >> intAux; //Puede no tener edificios
		//Mientras no lea centinela y no llene la lista de edificios comprados
		while ((intAux!= CENTINELA_EDIFICIOS) && (i < MAX_EDIFICIOS_COMPRADOS)){
			structAux.comprados.lista[i] = intAux;
			archivo >> intAux;

			i++;
		}
		//Actualizo contador de sublista edificios comprados
		structAux.comprados.contador = i;

		//Vuelco el aux en la lista (antes compruebo tamaño y agrando lista si necesario)
		if (listaJugadores.contador == listaJugadores.contadorMax)
			aumenta(listaJugadores);

		listaJugadores.lista[listaJugadores.contador] = structAux;
		listaJugadores.contador++;

		archivo.get(descarte);

		archivo.getline(structAux.usuario, TAM_CADENA); //Leo siguiente (o centinela o nombre del siguiente jugador)
	}
}

////////////////////////////
// *** CARGAR BINARIOS*** //
////////////////////////////

bool cargarBin(tListaEdificios &listaEdificios){
	fstream archivo;
	int pos, tam;
	bool salida = false;

	archivo.open(ARCHIVO_EDIFICIOS_BIN, ios::in | ios::binary);

	if (archivo.is_open()){
		salida = true;

		archivo.seekg(0, ios::end);
		pos = archivo.tellg();
		tam = pos / SIZE_tEdificio;

		archivo.seekg(0, ios::beg);
		for (int i = 0; i < tam; i++){
			//Compruebo tamaño y agrando si necesario
			if (listaEdificios.contador == listaEdificios.contadorMax)
				aumenta(listaEdificios);

			archivo.read((char*) &listaEdificios.lista[i], SIZE_tEdificio);
			listaEdificios.contador++;
		}
		archivo.close();
	}

	return salida;
}
bool cargarBin(tListaJugadores &listaJugadores){
	fstream archivo;
	int pos, tam;
	bool salida = false;

	archivo.open(ARCHIVO_JUGADORES_BIN, ios::in | ios::binary);

	if (archivo.is_open()){
		salida = true;

		archivo.seekg(0, ios::end);
		pos = archivo.tellg();
		tam = pos / SIZE_tJugador;

		archivo.seekg(0, ios::beg);
		for (int i = 0; i < tam; i++){
			//Compruebo tamaño y agrando si necesario
			if (listaJugadores.contador == listaJugadores.contadorMax)
				aumenta(listaJugadores);

			archivo.read((char*) &listaJugadores.lista[i], SIZE_tJugador);
			listaJugadores.contador++;
		}
		archivo.close();
	}

	return salida;
}   

//////////////////////////////
// *** GUARDAR BINARIOS *** //
//////////////////////////////

void guardarBin(tListaEdificios listaEdificios){
	fstream archivo;

	archivo.open(ARCHIVO_EDIFICIOS_BIN, ios::out | ios::binary | ios::trunc); // abrimos el archivo binario

	for (int i = 0; i < listaEdificios.contador; i++){
		archivo.write((char *) &listaEdificios.lista[i], SIZE_tEdificio);
	}

	archivo.close();
}
void guardarBin(tListaJugadores listaJugadores){
	fstream archivo;

	archivo.open(ARCHIVO_JUGADORES_BIN, ios::out | ios::binary | ios::trunc); // abrimos el archivo binario

	for (int i = 0; i < listaJugadores.contador; i++){
		archivo.write((char *) &listaJugadores.lista[i], SIZE_tJugador);
	}

	archivo.close();
}