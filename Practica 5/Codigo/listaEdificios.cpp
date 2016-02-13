#include "listaEdificios.h"

bool buscarEdificio(tListaEdificios listaEdificios, int buscado, int ini, int fin, int &pos) {
	bool encontrado = false;
	//Si no llego al final
	if (ini <= fin) {
		//Me coloco en la mitad
		int mitad = (ini + fin) / 2;
		//Si es el de la mitad, encontrado
		if (buscado == listaEdificios.lista[mitad].codigo) {
			pos = mitad;
			encontrado = true;
		}
		//Si no, compruebo si el buscado es mayor o menor al de la mitad, y sigo buscando por la izquierda (0 hasta mitad) o derecha (mitad a final)
		else
			if (buscado < listaEdificios.lista[mitad].codigo)
				encontrado = buscarEdificio(listaEdificios, buscado, ini, mitad - 1, pos);
			else
				encontrado = buscarEdificio(listaEdificios, buscado, mitad + 1, fin, pos);
	}
	return encontrado;
}

bool insertarEdificio(tListaEdificios &listaEdificios, tEdificio nuevoEdificio) {
	bool salida = false;
	int i = 0;

	//Busco posición
	while ((i < listaEdificios.contador) && (listaEdificios.lista[i].codigo < nuevoEdificio.codigo))
		i++;
	//Codigo duplicado? 
	if (listaEdificios.lista[i].codigo != nuevoEdificio.codigo) {
		//Lista llena? aumento tamaño (sólo aumentar si se va a introducir uno nuevo)
		if (listaEdificios.contador == listaEdificios.contadorMax)
			aumenta(listaEdificios);

		salida = true;
		//Desplazo
		for (int j = listaEdificios.contador; j > i; j--) 
			listaEdificios.lista[j] = listaEdificios.lista[j-1];
		//Inserto
		listaEdificios.lista[i] = nuevoEdificio;
		listaEdificios.contador++;
	}

	return salida;
}

bool bajaEdificio(tListaEdificios &listaEdificios, int codigo) 
{
	bool salida = false;
	//Busco posicion del codigo
	int pos;
	//Si encontrado (existe) y no comprado (la pos se actualiza antes de listaEdificios.lista[pos].estado)
	if (buscarEdificio(listaEdificios, codigo, 0, listaEdificios.contador - 1, pos) && (listaEdificios.lista[pos].estado != comprado)) {
		//return true y marco como borrado
		salida = true;
		listaEdificios.lista[pos].estado = borrado;
	}
	return salida;
}

void inicializa(tListaEdificios &listaEdificios) {
	listaEdificios.contador = 0;
	listaEdificios.lista = new tEdificio[TAM_INICIO_EDIFICIOS];
	listaEdificios.contadorMax = TAM_INICIO_EDIFICIOS;
}

void aumenta(tListaEdificios &listaEdificios){
	//Nuevo tamaño maximo
	int maxAux = ((listaEdificios.contadorMax * 3) / 2) + 1;

	//Nuevo espacio en el heap
	tPtrEdificio aux = new tEdificio[maxAux];

	//Muevo del espacio viejo al nuevo
	for (int i = 0; i < listaEdificios.contador; i++)
		aux[i] = listaEdificios.lista[i] ;

	//Libero espacio viejo
	delete [] listaEdificios.lista;

	//Actualizo lista con lso datos nuevos
	listaEdificios.lista = aux;
	listaEdificios.contadorMax = maxAux;
}