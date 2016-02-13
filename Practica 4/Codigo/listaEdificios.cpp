#include "listaEdificios.h"

bool buscarEdificio(tListaEdificios lista, int buscado, int &pos)
{
	//Busqeda binaria
	int fin = lista.contador - 1, mitad, ini = 0;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) 
	{
		mitad = (ini + fin) / 2; // División entera
		if (buscado == lista.lista[mitad].codigo)
			encontrado = true;
		else if (buscado < lista.lista[mitad].codigo)
			fin = mitad - 1;
		else
			ini = mitad + 1;
	}
	if (encontrado)
		pos = mitad;

	return encontrado;
}

bool insertarEdificio(tListaEdificios &lista, tEdificio nuevoEdificio) {
	bool salida = false;
	int i = 0;
	//Lista llena?
	if (lista.contador != MAX_EDIFICIOS)
	{
		//Busco posición
		while ((i < lista.contador) && (lista.lista[i].codigo < nuevoEdificio.codigo))
			i++;
		//Codigo duplicado? 
		if (lista.lista[i].codigo != nuevoEdificio.codigo)
		{
			salida = true;
			//Desplazo
			for (int j = lista.contador; j > i; j--) 
				lista.lista[j] = lista.lista[j-1];
			//Inserto
			lista.lista[i] = nuevoEdificio;
			lista.contador++;
		}
	}

	return salida;
}

bool bajaEdificio(tListaEdificios &edificios, int codigo) 
{
	bool salida = false;
	//Busco posicion del codigo
	int pos;
	//Si encontrado (existe) y no comprado
	if (buscarEdificio(edificios, codigo, pos) && (edificios.lista[pos].estado != comprado))
	{
		//return true y marco como borrado
		salida = true;
		edificios.lista[pos].estado = borrado;
	}
	return salida;
}