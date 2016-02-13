#include <iostream>
#include <string>
using namespace std;

#include <fstream>
#include <Windows.h>
#include <iomanip>

////////////////////////
// CONSTANTES Y TIPOS //
////////////////////////

typedef enum tDireccion
{
	nulo, derecha, arriba, izquierda, abajo,
};
typedef enum tColor
{
	negro, azulOscuro, verdeOscuro, turquesaOscuro, rojoOscuro, moradoOscuro, amarilloOscuro, blancoOscuro, 
	gris, azul, verde, turquesa, rojo, morado, amarillo, blanco, 
};

const short int 
	DIM = 20,
	NB = 10,

	LIBRE = -1,
	PARED = -2,
	AGUJERO = -3,
	VICTORIA = -4,

	CARACTER_PARED = 219,		
	CARACTER_AGUJERO = 177,
	CARACTER_BOLA = 254;

const tColor 
	COLOR_PARED = blanco,
	COLOR_AGUJERO = verdeOscuro,
	COLOR_BOLA = amarillo,
	COLOR_VICTORIA = rojo,
	COLOR_BASE = blanco;

const string 
	Extension = ".txt" , 
	ArchivoPorDefecto = "lab1.txt" ;

typedef short int tTablero[DIM][DIM];
typedef bool tBolas[NB];

typedef struct 
{
	tTablero tablero;
	tDireccion ultMovimiento;

	string nombreArchivo;
	int numBolas;
	int numTurnos;
}tJuego;

////////////////
// Prototipos //
////////////////

void setColor(tColor color);
bool bola_Caracter();
/* Función menú. Muestra menú en pantalla y pide opción
Devuelve un int como la opcióon elegida */
int menu();
/**/
void mostrar(tJuego juego, bool mostrar);
void inicializaJuego(tJuego& juego);
bool elegirTablero(tJuego& juego);
bool cargaJuego(tJuego& juego);
bool fronteraOK(int i, int j, int dato);
bool datoOK (int dato, int maxBolas, tBolas bolas);
bool validarFrontera(tTablero tablero);

void inclinarTablero(tJuego& juego, tDireccion direccion, bool& terminado);
void desplazarBola(tJuego& juego, int fila, int columna, tDireccion direccion, bool& terminado);

///////////////
// Funciones //
///////////////

int main()
{
	tJuego juego;
	int opcion;
	bool opcionValida = true, terminado = false, mostrarBola = bola_Caracter();

	inicializaJuego(juego);

	do
	{
		if (elegirTablero(juego))
		{
			do
			{
				if (opcionValida)
				{
					cout << endl ;
					mostrar(juego, mostrarBola);
					cout << endl ;
				}
				else
				{
					opcionValida = true;
				}
				opcion = menu();

				switch (opcion)
				{
				case 1:
				case 2:
				case 3:
				case 4:
					if (juego.ultMovimiento != tDireccion(opcion))
					{
						juego.ultMovimiento = tDireccion(opcion);
						inclinarTablero(juego, tDireccion(opcion), terminado);
						cout << endl << terminado << endl ;
						juego.numTurnos++;
					}
					else
					{
						cout << "Acabas de realizar esa jugada!" << endl ;
					}

					break;

				case 5: //Reinicio
					juego.numTurnos = 0;

					cargaJuego(juego);

					break;

				case 6: //Nuevo Tablero
					juego.nombreArchivo = ArchivoPorDefecto;
					juego.numTurnos = 0;
					juego.ultMovimiento = nulo;
				case 0: //Salir
					break;

				default: 
					cout << "¡Opcion no valida!" << endl ;
					opcionValida = false;
					break;
				}
			} while (opcion != 0 && opcion != 6 && !terminado);
		}
		else
		{
			opcion = 0; //Para salir
		}
	} while (opcion != 0 && !terminado);

	if (terminado)
	{
		cout << endl ;
		mostrar(juego, mostrarBola);
		cout << endl << "Felicidades!" << endl
			<< "Movimientos invertidos: " << juego.numTurnos ;
	}

	return 0;
}

void setColor(tColor color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, unsigned int (color));
}
bool bola_Caracter()
{
	char car;
	cout << "Desea mostrar el numero de bola o el caracter " << char (CARACTER_BOLA) << "? " << endl
		<< "(n para número, otro para caracter): " << endl ;
	cin >> car ;
	car = toupper(car);

	return (car == 'N');
}
void inicializaJuego(tJuego& juego) 
{
	juego.nombreArchivo = ArchivoPorDefecto;
	juego.numBolas = 0;
	juego.numTurnos = 0;
	//Todo a PARED (-2)
	for (int fila = 0; fila < DIM; fila++) 
		for (int col = 0; col < DIM; col++) 
			juego.tablero[fila][col] = PARED;

	juego.ultMovimiento = nulo;
}
int menu()
{
	int opcion ;

	setColor(COLOR_BASE);

	cout << "1 - Inclinar hacia la derecha" << endl
		<< "2 - Inclinar hacia arriba" << endl
		<< "3 - Inclinar hacia la izquierda" << endl
		<< "4 - Inclinar hacia abajo" << endl
		<< "5 - Reiniciar el tablero" << endl
		<< "6 - Cargar nuevo tablero" << endl
		<< "0 - Salir" << endl
		<< "Opcion: ";

	cin >> opcion;

	return opcion;
}

void mostrar(tJuego juego, bool mostrar)
{
	short int leido;
	cout << setw(DIM * 3) << juego.numTurnos << endl ;
	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			leido = juego.tablero[i][j];
			switch (leido)
			{
			case PARED:
				setColor(COLOR_PARED);
				cout << char(CARACTER_PARED) << char(CARACTER_PARED) << char(CARACTER_PARED) ;
				break;
			case AGUJERO:
				setColor(COLOR_AGUJERO);
				cout << char(CARACTER_AGUJERO) << char(CARACTER_AGUJERO) << char(CARACTER_AGUJERO) ;
				break;
			case VICTORIA:
				setColor(COLOR_VICTORIA);
				cout << char(CARACTER_AGUJERO) << char(CARACTER_AGUJERO) << char(CARACTER_AGUJERO) ;
				break;
			case LIBRE:
				cout << "   " ;
				break;
			default:
				{
					setColor(COLOR_BOLA);
					if (mostrar)
					{
						cout << ' ' << leido << ' ' ;
					}
					else
					{
						cout << ' ' << char(CARACTER_BOLA) << ' ' ;
					}
					break;
				}
			}
		}
		cout << endl ;
	}
}

bool elegirTablero(tJuego& juego)
{
	string entrada;
	do
	{
		cout << "Introduzca tablero con el que jugar" << endl
			<<"Por defecto lab1.txt, 0 para salir: " ;

		cin.sync();
		getline(cin, entrada);

		if (entrada != "0" && entrada != "")
		{
			//Comprobar si está la extensión txt al final, para añadirla

			//Para evitar acceder a posiciones erróneas, comprobamos si el tamaño es al menos 4, 
			//por shortcut para OR si es menor que 4 no comprueba si acaba en .txt (entraría a posiciones no existentes) y añade el .txt
			if ((entrada.size() < 4) || (entrada.substr(entrada.size() - 4, 4) != Extension))
			{
				entrada += Extension;
			}
			juego.nombreArchivo = entrada;
		}
	} while ((entrada != "0" || entrada != "") && !cargaJuego(juego));

	return entrada != "0";
}

bool cargaJuego(tJuego& juego)
{
	tBolas bolasIntroducidas = {false}; // Para bolas repetidas
	ifstream archivo;

	int i = 0, j = 0, leido;

	bool salir = false;

	archivo.open(juego.nombreArchivo.c_str());
	//Ver si archivo existe
	if (archivo.is_open())
	{
		archivo >> juego.numBolas;

		if (juego.numBolas <= NB)
		{
			while ((i < DIM) && !salir)
			{
				j = 0;
				while ((j < DIM) && !salir)
				{
					archivo >> leido;
					//Comprobar si frontera es Pared
					if (fronteraOK(i, j, leido))
					{
						//Comprobar si dato es pared, vacio, agujero o bola (y no repite bola)
						salir = !datoOK(leido, juego.numBolas, bolasIntroducidas);
						if (!salir)
						{
							if (!archivo.eof()) //Si fin de archivo, el tablero no es de DIM x DIM
							{
								juego.tablero[i][j] = leido;
								j++;
							}
							else
							{
								cout << "Error: El tablero del archivo no es de " << DIM << " x " << DIM << " o falta numero de bolas" << endl ;
								salir = true;
							}
						}
					}
					else
					{
						cout << "Error: frontera erronea " << endl ;
						salir = true;
					}
				}
				i++;
			}
			//Si salir = true, hay un error, por tanto tenemos que return false, y iceversa (salir es el dato de retorno de la funcion)
			salir = !salir;
		}
		else
		{
			cout << "Error: hay mas de " << NB << " bolas en el archivo." << endl ;
			salir = false;
		}
		archivo.close();
	}
	else
	{
		cout << "Error de apertura del archivo " << juego.nombreArchivo << "." << endl ;
		salir = false;
	}
	if (!salir)
	{
		juego.nombreArchivo = ArchivoPorDefecto ; //Devolver valor por defecto
	}
	return salir;
}
bool fronteraOK(int i, int j, int dato)
{
	bool salida = true;

	if ((i == 0) || (i == DIM - 1) || (j == 0) || (j == DIM - 1))
	{
		salida = (dato == PARED);
	}
	//else salida = true
	return salida;
}
bool datoOK (int dato, int maxBolas, tBolas bolas)
{
	bool salida = false;

	if ((dato == LIBRE) || (dato == PARED) || (dato == AGUJERO))
	{
		salida = true;
	}
	else if ((dato >= 0) && (dato < maxBolas))
	{
		if (bolas[dato])
		{
			cout << "Error: se repite una bola." << endl ;
		}
		else
		{
			bolas[dato] = true;
			salida = true;
		}
	}
	else
	{
		cout << "Error: algun dato del archivo no es valido." << endl ;
	}

	return salida;
}

void inclinarTablero(tJuego& juego, tDireccion direccion, bool& finJuego)
{
	int fila = 1, columna = 1, leido;
	bool terminado = false;

	switch (direccion)
	{
	case derecha:
		while (fila < (DIM - 1)/*  && !terminado */)
		{
			columna = DIM - 2;
			while (columna > 0/*  && !terminado */)
			{
				leido = juego.tablero[fila][columna]; 
				if (leido >= 0) //Si tenemos bola
				{
					desplazarBola(juego, fila, columna, direccion, terminado);
					finJuego = finJuego || terminado;
				}
				columna--;
			}
			fila++;
		}
		break;
	case arriba:
		while (fila < (DIM - 1)/*  && !terminado */)
		{
			columna = 1;
			while (columna < (DIM - 1)/*  && !terminado */)
			{
				leido = juego.tablero[fila][columna];
				if ((leido >= 0) && (leido <= juego.numBolas))
				{
					desplazarBola(juego, fila, columna, direccion, terminado);
					finJuego = finJuego || terminado;
				}
				columna++;
			}
			fila++;
		}
		break;
	case izquierda:
		while (fila < (DIM - 1)/*  && !terminado */)
		{
			columna = 1;
			while (columna < (DIM - 1)/*  && !terminado */)
			{
				leido = juego.tablero[fila][columna];
				if ((leido >= 0) && (leido <= juego.numBolas))
				{
					desplazarBola(juego, fila, columna, direccion, terminado);
					finJuego = finJuego || terminado;
				}
				columna++;
			}
			fila++;
		}
		break;
	case abajo:
		fila = DIM - 2;
		while (fila > 0/*  && !terminado */)
		{
			columna = 0;
			while (columna < (DIM - 1)/*  && !terminado */)
			{
				leido = juego.tablero[fila][columna];
				if ((leido >= 0) && (leido <= juego.numBolas))
				{
					desplazarBola(juego, fila, columna, direccion, terminado);
					finJuego = finJuego || terminado;
				}
				columna++;
			}
			fila--;
		}
		break;
	}
}
void desplazarBola(tJuego& juego, int fila, int columna, tDireccion direccion, bool& terminado)
{
	short int incrFila = 0, incrColumna = 0, leido, i = 0, j = 0, bola = juego.tablero[fila][columna];
	bool salir = false;

	switch (direccion)
	{
	case arriba:
		incrFila = -1;
		break;
	case abajo:
		incrFila = 1;
		break;
	case izquierda:
		incrColumna = -1;
		break;
	case derecha:
		incrColumna = 1;
		break;
	}
	i = incrFila;
	j = incrColumna;
	while (!salir)
	{
		//Leido es lo siguiente a la bola
		leido = juego.tablero[fila + i][columna + j];

		salir = ((leido == PARED) || (leido >= 0)); //Si es pared o bola salimos

		if (!salir)
		{
			if (leido == AGUJERO || leido == VICTORIA) //Si encuentro un agujero
			{
				leido = juego.tablero[fila + i + incrFila][columna + j + incrColumna]; //Leo el siguiente

				terminado = ((leido == PARED) || (leido >= 0)); //Si el siguiente al agujero es bola o libre, termino (la bora se para en agujero)
				salir = terminado;
				juego.tablero[fila + i][columna + j] = (terminado ? VICTORIA : AGUJERO); //Colocamos la victoria si despues hay bola o pared, o agujero si hay libre
			}
			else
			{
				juego.tablero[fila + i][columna + j] = bola; //Muevo la bola hacia adelante
			}
			juego.tablero[fila + i - incrFila][columna + j - incrColumna] = ((juego.tablero[fila + i - incrFila][columna + j - incrColumna] == AGUJERO) ? AGUJERO : LIBRE); //El anterior queda libre
			i += incrFila;
			j += incrColumna;
		}
	}
}

