//////////////////////////////////////////////
//													     //
//					  PRÁCTICA 2					  //
//													     //
//			     PORTAL DE JUEGOS			     //
//													     //
//				Miguel Ascanio Gómez			     //
//				Javier Ortiz Iniesta			     //
//													     //
//////////////////////////////////////////////
// I.A. Explciada en prototipo juegaOrdenador_Voltear (linea 126)

#include <iostream>
#include <string>
using namespace std;

#include <cstdlib>
#include <ctime>
#include <fstream>

typedef enum tTurno
{ 
	jugador, ordenador
};
typedef enum tJugadaSpock
{
	piedra, papel, tijeras, lagarto, spock
};
typedef enum tDireccion
{ 
	N, S, E, O
};
typedef enum tResultado
{
	empate, victoriaJugador, derrotaJugador
};
typedef enum tOpcionesMenu
{
	salir, reglasPiedra, jugarSpock, reglasDado, jugarDado
};

//////////////////////////////////////////////////////////////////////////////////////////////

const int LIMITE = 50;
/*
Función que realiza las acciones relacionadas con el registro y logueo mediante las funciones a continuación, permitirá jugar o no.
Devuelve: un bool, true si el logueo se hace correctamente (teniendo encuenta la contraseña y apertura de arcchivos)
*/
bool logInOK();
/*
Función que comprueba si el apodo introducido en logInOK() existe en registro.txt (recorre el archivo)
Entrada: el apodo introducido en logInOK() (string)
Devuelve: por parametros por variable devuelve dos bool aperturaOK que indica si los archivos abren correctamente,
contraseñaOK si la contraseña es correcta; en el return devuelve si el apodo existe
*/
bool apodoExistente(bool &aperturaOK, bool &contrasenaOK, string &apodo);
/*
Función que pide la contraseña hasta tres veces (en caso de existir el usuario)
Entrada: la contraseña leida del archivo (string)
Devuelve: bool que indica si se ha introducido bien la contraseña (antes de los 3 fallos) o no
*/
bool comprobarContrasena(string contrasenaLeida);
/*
Funcion que se encarga de registrar el usuario en registro.txt 
Entrada: apodo introducido en logInOK() (string)
Devuelve: bool para indicar apertura correcta de los archivos
*/
bool registrarUsuario(string apodo);

/*
Funcion que muestra el menu y pide opctiones mientras no se introduzca una correcta.
Devuelve: opción convertida a tOpcionesMenu {salir, reglasPiedra, jugarSpock, reglasDado, jugarDado}
*/
tOpcionesMenu menu();
/*
Procedimiento que muestra el contenido del archivo pasado como argumento por variable ifstream.
El mismo comprueba su apertura y lo cierra.
*/
void lecturaReglas(ifstream &lectura);

/*
Procedimiento principal del juego spock, en el se invocan los subprogramas de jugadas de usuario y ordenador, asi como la evaluacion de jugadas.
Muestra en pantalla las jugadas y el resultado
Modifica los contadores de victoria, derrota y empate pertintentes (parametros por variable tipo int)
*/
void juego_Spock(int &victorias, int &derrotas, int &empates);
/*
Funcion que pide al usuario que haga su jugada hasta que meta una correcta.
Devuelve la jugada como  tJugadaSpock { piedra, papel, tijeras, lagarto, spock }
*/
tJugadaSpock juegaUsuario_Spock();
/*
Funcion que realiza la jugada de la computadora por miedio de un rand
Devuelve la jugada como tJugadaSpock { piedra, papel, tijeras, lagarto, spock }
*/
tJugadaSpock juegaOrdenador_Spock();
/*
Funcion que compara las jugadas del ordenador y del usuario, determinando quien gana
Entrada: las jugadas del usuario y del ordenador (tJugadaSpock)
Salida: el resultado como tResultado { empate, victoriaJugador, derrotaJugador }
*/
tResultado evaluarJugada_Spock(tJugadaSpock jugadaUsuario, tJugadaSpock jugadaOrdenador);

/*
Procedimiento principal del juego voltear el dado, en el se invocan los subprogramas a continuacion para el juego
Modifica los contadres victoria y derrota
*/
void juegoVoltear(int &victorias, int &derrotas);
/*
Procedimiento que realiza la tirada aleatoria inicial. Elije aleatoriamente la superior, las otras van determinadas por la superior
Midifica las tres caras
*/
void colocarDado(int &caraSuperior, int &caraFrontal, int &caraLateral);
/*
Procedimiento que dibuja el dado y suma al contador la cara superior
Entradas: las caras del dado y el estado actual del contador
Devuelve: la cara superior sumada al contador / contador += cara superior
*/
void dibujarDado(int caraSuperior, int caraFrontal, int caraLateral, int &contador);
/*
Procedimiento que cambia el turno
Modifica el parametro por valor: si entra como ordenador, sale como jugador y viceversa. tipo tTurno
*/
void cambioTurno(tTurno &turno);

/*
Función que realiza la jugada del ordenador.
Busca jugar el número más alto posible (para acortar la partida) hasta que el contador está a menos de 12 del límite, en cuyo caso busca jugar el 1.
Siempre que pueda poner el contador en 49 (de tal manera que gana) bucsa el giro adecuado. Si para llegar a 49 el numero esta tapado (superior o inferior) juega el 1
En caso de pretender jugar un número y estar tapado (cara superior o inferior) busca el anterior. En caso de pretender jugar el 1 y estar tapado, juega el 2.
Entradas: caras y contador
Devuelve: el giro del dado (su jugada) como tDireccion {N S E O}
*/
tDireccion juegaOrdenador_Voltear(int caraSuperior, int caraFrontal, int caraLateral, int contador);
/*
Procedimiento que gira el dado según la dirección pasada como argumento
Entrada: direccion de giro y caras del dado.
Devuelve: las Caras modificadas segun el giro
*/
void girarDado(tDireccion direccion, int &caraSuperior, int &caraFrontal, int &caraLateral);
/*
Funcion que solicita al usuario introducir su jugada (la vuelve a pedir si errónea), salir del juego o mostrar las reglas
Devuelve: el giro que quiere efectuar el usuario como tTgiro, parametro por variable terminar del tipo bool para terminar el juego
*/
tDireccion juegaUsuario_Voltear(bool &terminar);

/*
Funciones que devuelve el valor la variable (tJugadaSpock o tDireccion) como String (N -> "Norte"; spock -> "Spock") 
Entrada: enumerado del tipo tJugadaSpock o tDireccion
Devuelve: el String correspondiente
*/
string enumToString(tJugadaSpock enumSpock); 
string enumToString(tDireccion enumDireccion); 

//////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////
// LOGUEO / REGISTRO //
///////////////////////

bool logInOK()
{
	string apodo;	

	bool aperturaOK = true, 
		contrasenaOK,
		salida = true;

	if (apodoExistente(aperturaOK, contrasenaOK, apodo))
	{
		if (!contrasenaOK || !aperturaOK) //Si fallamos conrtaseña o archivo no abre, loginOK -> return false y no deja jugar
			salida = false;
	}
	else if(aperturaOK)
		salida = registrarUsuario(apodo);

	return salida && aperturaOK;
}

bool apodoExistente(bool &aperturaOK, bool &contrasenaOK, string &apodo)
{
	//Variables fstream para archivos de texto
	ifstream lectura;
	ofstream escritura;

	string lineaArchivo;	//Usado para leer de los .txt

	bool apodoExistente = false;	//Usadas en registro

	//Inicio lectura/escritura en registro y temp
	lectura.open("registro.txt");
	escritura.open("temp.txt");

	if (lectura.is_open() && escritura.is_open()) //Comprobar si abren
	{
		//Leer de registro y escribir en temp mientras no se lea el apodo o el centinela XXX
		//al leer apodo existente, comprobar contraseña

		cout << "Por favor, introduce tu apodo: " ;
		cin >> apodo; 

		do
		{
			lectura >> lineaArchivo;			
			escritura << lineaArchivo << endl ;	
			if (lineaArchivo == apodo) 
			{
				apodoExistente = true;
				lectura >> lineaArchivo; 

				contrasenaOK = comprobarContrasena(lineaArchivo); //se comprueba la contraseña en la función
			}
			else if(lineaArchivo != "XXX")
			{
				lectura >> lineaArchivo ; //descarta la contraseña (para evitar errores si coinciden un usuario y una contraseña)
				escritura << lineaArchivo << endl ;
			}

		} while (!apodoExistente && (lineaArchivo != "XXX")); 
	}
	else //error si no abre
	{
		cout << endl << "No existe el archivo de registro!" << endl ;
		aperturaOK = false;
	}
	//Cerrar archivos
	lectura.close();
	escritura.close();

	return apodoExistente;
}
bool registrarUsuario(string apodo)
{
	//Variables fstream para archivos de texto
	ifstream lectura;
	ofstream escritura;

	string contrasena,				//Contraseña
		lineaArchivo;					//Usado para leer de los .txt

	bool aperturaOK = true,
		apodoExistente = false;	

	//Inicio lectura/escritura en registro y temp
	lectura.open("temp.txt");			
	escritura.open("registro.txt");

	if (escritura.is_open() && lectura.is_open()) //Continuar si los archivos abren
	{
		do 
		{
			lectura >> lineaArchivo;
			if (lineaArchivo != "XXX")
				escritura << lineaArchivo << endl;
			else //Cuando se lee el centinela, escribir apodo introducido, solicitar contraseña y escribirla
			{
				escritura << apodo << endl ;
				cout << "Elige una contraseña: " ;
				cin >> contrasena ;

				escritura << contrasena << endl << "XXX" ; //escribe la contraseña y el centinela XXX
			}
		} while  (lineaArchivo != "XXX");
	}
	else
	{
		cout << "Fallo de apertura de archivo!!";
		aperturaOK = false;
	}

	//Cerrar archivos
	escritura.close();
	lectura.close();

	return aperturaOK;
}
bool comprobarContrasena(string contrasenaLeida)
{
	string contrasena;
	bool contrasenaOK;
	int fallos = 0;

	cout << "Contraseña: " ;
	do //Pedir contraseña, hasta 3 veces
	{
		contrasenaOK = false;
		cin >> contrasena;
		if (contrasena == contrasenaLeida)
			contrasenaOK = true;
		else
		{
			if (fallos < 2) // A los dos fallos, error
				cout << "Contraseña incorrecta! Vuelve a intentarlo: " ;
			fallos++;
		}
	} while (!contrasenaOK && fallos < 3);
	if (!contrasenaOK)
		cout << "Lo siento, pero has fallado demasiadas veces. No puedes jugar." ;

	return contrasenaOK;
}

///////////////////
// MENÚ / REGLAS //
///////////////////

tOpcionesMenu menu()
{
	int opcion = -1; 
	while (opcion < 0 || opcion > 4) //Al introducir 0 en opción, fin. 
	{
		//Mostrar menú y pedir opción
		cout << endl 
			<< "Elige lo que quieres hacer:" << endl
			<< "1. Ver insturcciones de Rock-Paper-Scissors-Lizard-Spock" << endl
			<< "2. Jugar a Rock-Paper-Scissors-Lizard-Spock" << endl
			<< "3. Ver instrucciones de Voltear el dado" << endl
			<< "4. Jugar a Voltear el dado" << endl
			<< "0. Salir" << endl
			<< "Opción: " ;
		cin.sync();
		cin >> opcion ;

		if (opcion < 0 || opcion > 4)
			cout << "La opción no es correcta" << endl;
	}
	return tOpcionesMenu(opcion);
}

void lecturaReglas(ifstream &lectura)
{
	string lineaArchivo;

	cout << endl ;

	if (lectura.is_open())
	{
		do //muestra en pantalla la linea que se lee del reglas.txt (con getline), hasta encontrar el XXX
		{
			getline(lectura, lineaArchivo);
			if (lineaArchivo != "XXX") //No mostrar XXX
				cout << lineaArchivo << endl ;
		} while (lineaArchivo != "XXX");
	}
	else
		cout << "Lo siento, pero no encuentro el archivo con las reglas!" << endl ;

	lectura.close(); //cierre
}

/////////////////
// JUEGO SPOCK //
/////////////////

void juego_Spock(int &victorias, int &derrotas, int &empates)
{	
	cout << endl ;
	string entradaJugada;	//Leer jugada
	
	tJugadaSpock jugadaUsuario = juegaUsuario_Spock(), //
			   jugadaOrdenador = juegaOrdenador_Spock(); // Se ejecutan las funciones jugada

	cout << endl //se muestran las jugadas
		<< "Mi elección: " << enumToString(jugadaOrdenador) << endl
		<< "Tu elección: " << enumToString(jugadaUsuario) << endl
		<< "........." << endl ;
	
		//se evaluan las jugadas mediante la funcion y se muestra elo resultado, tambien se acumula al contador
		switch (evaluarJugada_Spock(jugadaUsuario, jugadaOrdenador))
	{
	case empate:
		cout << "Empate!" ;
		empates++ ;
		break;
	case victoriaJugador:
		cout << "Tú ganas!" ;
		victorias++ ;
		break;
	case derrotaJugador:
		cout << "Gano yo!" ;
		derrotas++ ;
		break;
	}
	cout << endl << endl ;
}
tJugadaSpock juegaUsuario_Spock()
{
	tJugadaSpock jugadaUsuario;
	string entradaJugada;

	bool entradaJugadaOK = false;	//Usado para comprobar jugada

	while (!entradaJugadaOK) //Bucle selección elemento
	{
		cout << "Elige elemento: (piedra, papel, tijeras, lagarto o spock): "  ;
		cin >> entradaJugada ;   

		//Si se introduce una jugada válida, asignarla el tJugadaSpock; 
		entradaJugadaOK = true;
		if (entradaJugada == "piedra")
			jugadaUsuario = piedra;
		else if (entradaJugada == "papel")
			jugadaUsuario = papel;
		else if (entradaJugada == "tijeras")
			jugadaUsuario = tijeras;
		else if (entradaJugada == "lagarto")
			jugadaUsuario = lagarto;
		else  if (entradaJugada == "spock")
			jugadaUsuario = spock;
		else //Jugada introducida no valida: mostrar error y volver a solicitar
		{
			cout << "Elemento desconocido. Inténtalo de nuevo." << endl;
			entradaJugadaOK = false;
		}
	}

	return jugadaUsuario;
}
tJugadaSpock juegaOrdenador_Spock()
{
	tJugadaSpock jugadaOrdenador;

	switch (rand() % 5)//Elección del ordenador (dentro de los () del switch), asignar a tJugadaSpock y mostrar
	{
	case 0: jugadaOrdenador = piedra;	break;
	case 1: jugadaOrdenador = papel;		break;
	case 2: jugadaOrdenador = tijeras;	break;
	case 3: jugadaOrdenador = lagarto;  break;
	case 4: jugadaOrdenador = spock;		break;
	}
	return jugadaOrdenador;
}
tResultado evaluarJugada_Spock(tJugadaSpock jugadaUsuario, tJugadaSpock jugadaOrdenador)
{
	bool ganaOrdenador = false;	
	tResultado salida = empate;

	if (jugadaUsuario != jugadaOrdenador) //Si jugadas iguales, empate
	{
		switch (jugadaUsuario)	//Evaluar jugadas del usuario en las que pierde: ganaOrdenador = true; si no, se mantiene el false
		{
		case piedra:
			if (jugadaOrdenador == papel || jugadaOrdenador == spock) 
				ganaOrdenador= true;
			break;
		case papel:
			if (jugadaOrdenador == tijeras || jugadaOrdenador == lagarto)
				ganaOrdenador= true;
			break;
		case tijeras:
			if (jugadaOrdenador == piedra || jugadaOrdenador == spock)
				ganaOrdenador= true;
			break;
		case lagarto:
			if (jugadaOrdenador == piedra || jugadaOrdenador == tijeras)
				ganaOrdenador= true;
			break;
		case spock:
			if (jugadaOrdenador == papel || jugadaOrdenador == lagarto)
				ganaOrdenador= true;
			break;
		}
		if (ganaOrdenador)
			salida = derrotaJugador;

		else //Si el ordenador no gana
			salida = victoriaJugador;
	}	
	return salida;
}

///////////////////
// JUEGO VOLTEAR //
///////////////////

void juegoVoltear(int &victorias, int &derrotas)
{
	int caraSuperior, caraFrontal, caraLateral, contador = 0;
	tTurno turno = tTurno(rand() % 2);	//Quién empieza
	tDireccion direccionGiro;				//Direccion de giro para usuario u ordenador
	bool terminar = false;

	//coloca aleatoriamente el dado
	colocarDado(caraSuperior, caraFrontal, caraLateral);

	cout << endl 
		<< "\t" << "-------------------------" << endl
		<< "\t" << "|  BIENVENIDO AL JUEGO  |" << endl
		<< "\t" << "|    VOLTEAR EL DADO    |" << endl 
		<< "\t" << "-------------------------" << endl 
		<< endl << endl
		<< "COMIENZA EL JUEGO... ¿Quién empieza?" << endl << endl ;

	if (turno == jugador)
		cout << "Empiezas tú" << endl 
		<< "Tu tirada del dado ha sido" << endl ;
	else
		cout << "Empiezo yo" << endl 
		<< "Mi tirada del dado ha sido" << endl ;

	//Muetsra dado inicial
	dibujarDado(caraSuperior, caraFrontal, caraLateral, contador);
	//Bucle principal juego volear
	while (!terminar)
	{
		cambioTurno(turno); //se cambia de turno
		 
		//Jugadas
		if (turno == ordenador)
		{
			cout << "Me toca a mí" << endl ; 

			//Ordenador juega y la muestra como string
			direccionGiro = juegaOrdenador_Voltear(caraSuperior, caraFrontal, caraLateral, contador);		
			cout << "Mi jugada es " << enumToString(direccionGiro) << endl;
		}
		else //Usuario juega
			direccionGiro = juegaUsuario_Voltear(terminar);
		
		//Se gira el dado según la jugada
		girarDado(direccionGiro, caraSuperior, caraFrontal, caraLateral);

		if(!terminar)
			dibujarDado(caraSuperior, caraFrontal, caraLateral, contador);

		if ((contador >= LIMITE) && !terminar)
		{
			terminar = true;

			if (turno == ordenador)
			{
				cout << "HAS GANADO !!!!!!" << endl ;
				victorias++;
			}
			else
			{
				cout << "HAS PERDIDO !!!!!!" << endl ;
				derrotas++;
			}
		}
	}
}

void colocarDado(int &caraSuperior, int &caraFrontal, int &caraLateral)
{
	caraSuperior = rand() % 5 + 1;
	switch (caraSuperior)
	{
	case 1: caraFrontal = 5; caraLateral = 4; break;
	case 6: caraFrontal = 2; caraLateral = 4; break;
	case 2: caraFrontal = 4; caraLateral = 6; break;
	case 5: caraFrontal = 1; caraLateral = 3; break;
	case 3: caraFrontal = 1; caraLateral = 2; break;
	case 4: caraFrontal = 5; caraLateral = 6; break;
	}
}
void dibujarDado(int caraSuperior, int caraFrontal, int caraLateral, int &contador)
{
	contador += caraSuperior;

	cout 
		<<	"     __" << endl 
		<< "   / " <<  caraSuperior << " / |" << endl
		<<"   -- |" << caraLateral << " |           Contador = " << contador << endl
		<<"  | " << caraFrontal <<" | /" << endl
		<<"   --"  << endl 
		<< endl ;
}
void cambioTurno(tTurno &turno)
{
	switch (turno)
	{
	case jugador: turno = ordenador;
		break;
	case ordenador: turno = jugador;
		break;
	}
}

//Giro Dado
void girarDado(tDireccion direccion, int &caraSuperior, int &caraFrontal, int &caraLateral)
{		
	int aux = caraSuperior;

	switch (direccion)
	{
	case N:
		caraSuperior = caraFrontal;
		caraFrontal = 7 - aux;
		break;
	case S:
		caraSuperior = 7 - caraFrontal;
		caraFrontal = aux;
		break;
	case E:
		caraSuperior = 7 -
			caraLateral;
		caraLateral = aux;
		break;
	case O:
		caraSuperior = caraLateral;
		caraLateral = 7 - aux;
		break;
	}
}

//Juega Ordenador (elije dirección)
tDireccion juegaOrdenador_Voltear(int caraSuperior, int caraFrontal, int caraLateral, int contador)
{
	int numAJugar = LIMITE - contador ; //Distancia al limite
	tDireccion salida;

	//Elegir numero a jugar (máximo posible, buscar 49, a 12 del limite jugar 1)
	if (numAJugar > 6)
		if (numAJugar <= 12)
		{
			numAJugar = 1;
		}
		else
		{
			numAJugar = 6;
		}
	else if (numAJugar != 1)
	{
		numAJugar--;
	}

	//Jugada tapada? -> buscar el anterior (si es el 1 juega el 2, 
	if ((caraSuperior == numAJugar) || (7 - caraSuperior == numAJugar)) 
	{
		if (numAJugar == 1)
		{
			numAJugar = 2;
		}
		else
		{
			numAJugar--;
		}
	}

	//Bucar cara del numero a jugar
	if (numAJugar == caraFrontal)
	{
		salida = N;
	}
	else if (numAJugar == 7 - caraFrontal)
	{
		salida = S;
	}
	else if (numAJugar == caraLateral)
	{
		salida = O;
	}
	else
	{
		salida = E;
	}

	return salida; //devolver la cara
}

//Juega Usuario (elije dirección)
tDireccion juegaUsuario_Voltear(bool &terminar)
{
	tDireccion salida = O;
	ifstream archivo;
	char opcion;
	bool opcionOK = false;

	cout << "Te toca elegir jugada" << endl  ;

	while (!opcionOK) //pedir mientras opcion erronea o mostrar reglas
	{
		opcionOK = true;

		cout << endl
			<< "Indica el giro que quieres hacer mediante un punto cardinal (N, S, E, O)" << endl 
			<< "Si quieres ver las instrucciones pulsa 1. Si quieres terminar pulsa 0" << endl
			<< "Elección: " ;
		cin.sync();
		cin >> opcion;
		opcion = toupper(opcion);

		switch (opcion)
		{
		case '1': 
			archivo.open("reglasVoltear.txt");
			lecturaReglas(archivo); opcionOK = false; 
			break;
		case '0': terminar = true; break;
		case 'N': salida = N; break;
		case 'S': salida = S; break;
		case 'E': salida = E; break;
		case 'O': salida = O; break;
		default: opcionOK = false; break;
		}
	}
	return salida;
}

//Paso de enumerado a String
string enumToString(tDireccion enumDireccion)
{
	string salida;
	switch (enumDireccion)
	{
	case N: salida = "Norte"; break;
	case S: salida = "Sur"; break;
	case E: salida = "Este"; break;
	case O: salida = "Oeste"; break;
	}
	return salida;
}
string enumToString(tJugadaSpock enumSpock)
{
	string salida;
	switch (enumSpock)
	{
	case piedra:	salida = "Piedra" ;	break;
	case papel:		salida = "Papel" ; break;
	case tijeras:	salida = "Tijeras" ; break;
	case lagarto:	salida = "Lagarto" ; break;
	case spock:		salida = "Spock" ; break;
	}
	return salida;
}

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	system("chcp 1252");
	srand(time(NULL));

	ifstream archivo; //Usado en opcion 1 y 3, lectura de reglas de ambos juegos (se abre el archivo y se pasa la variable a la funcion recorrido de archivo lecturaReglas(..))

	int victorias_Spock = 0,		//
		empates_Spock = 0,			//
		derrotas_Spock = 0,			// Contadores
		victorias_Voltear = 0,		//
		derrotas_Voltear = 0;		//

	tOpcionesMenu opcion;

	if (logInOK()) //se ejecuta lo referente al logueo (conrtaseña, registro..) solo permite jugar si loguea OK (incluyendo fallo de apertura de archivos)
	{
		cout << endl 
			<< "----------------------------------" << endl
			<< "  BIENVENIDO AL PORTAL DE JUEGOS   " << endl
			<< "----------------------------------" << endl ;

		do
		{
			opcion = menu(); //se ejecuta el menu y se obtiene la opcion evaluada en el switch
			switch (opcion)
			{
			case jugarSpock: 
				juego_Spock(victorias_Spock, derrotas_Spock, empates_Spock);
				break;

			case reglasPiedra: 
				archivo.open("reglasSpock.txt");
				lecturaReglas(archivo);
				break;

			case jugarDado:
				juegoVoltear(victorias_Voltear, derrotas_Voltear);
				break;

			case reglasDado: 
				archivo.open("reglasVoltear.txt");
				lecturaReglas(archivo);
				break;

			case salir: //mostrar contadores y salir

				cout << endl  
					<< "El número total de partidas Spock jugadas ha sido " << victorias_Spock + derrotas_Spock + empates_Spock << endl 
					<< "El número total de partidas ganadas ha sido " << victorias_Spock << endl
					<< "El número total de partidas empatadas ha sido " << empates_Spock << endl
					<< "El número total de partidas perdidas ha sido " << derrotas_Spock << endl 
					<< endl
					<< "El número total de partidas Voltear jugadas ha sido " << victorias_Voltear + derrotas_Voltear << endl
					<< "El número total de partidas ganadas ha sido " << victorias_Voltear << endl
					<< "El número total de partidas perdidas ha sido " << derrotas_Voltear << endl
					<< endl
					<< "Hasta pronto!" ;

				break;
			}
		} while (opcion != salir);
	}

	cout << endl << "Pulsa Intro..." ;
	cin.sync();
	cin.get();

	return 0;
}
