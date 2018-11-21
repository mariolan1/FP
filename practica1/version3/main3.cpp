
/*
	*Practica 1 FP Version 3.
	*Nombre y apellido : Wenhui Lin   
	*Nombre y apellido : Wenbo Sun
*/



/*--------------------------------------------------------------------------
								Librearias
--------------------------------------------------------------------------*/
#include <iostream> //console input and output
#include <iomanip>	//manipular espacios
#include <cstdlib>  //random
#include <string>	//string variables
#include <fstream>	//  in/out put files
#include <algorithm> //random_shuffle

//espacio de nombres std para string, cin/cout
using namespace std;

/*--------------------------------------------------------------------------
						Tipos definidos
--------------------------------------------------------------------------*/

//constante que representa las diez cartas 1-7 ---- 10-12 de la baraja espanola
const int N = 10; 

//array que guarda las cartas por aparecer del mazo
typedef int tCartasPorAparecer[N]; 


//constante maximo de cartas de la baraja espanola
const int M = 40;

//array cartas que forman el mazo
typedef int tArrayCartas[M]; 

//el mazo de carta con su contador de cartas
typedef struct {
	tArrayCartas lista;
	int contador;
}tConjuntoCartas;

/*--------------------------------------------------------------------------
								Subprogramas
--------------------------------------------------------------------------*/

/* Permite a cualquiera de los dos jugadores realizar su turno del modo A 
en una partida.Recibe el archivo con el mazo y el número de cartas que hay
que robar, y devuelve los puntos obtenidos tras robar ese número de cartas.
*/
float modoA(ifstream &file, int numCartas);


/*  Permite realizar el turno del jugador humano en el modo B. Recibe el 
archivo con el mazo y el número máximo de cartas que puede robar, y devuelve 
los puntos obtenidos.*/
float modoBhumano(ifstream &file, int numCartas);

/* Permite realizar el turno del jugador máquina en el modo B. Recibe el
archivo con el mazo, el número máximo de cartas que puede robar y la 
puntuación obtenida por el jugador humano, y devuelve los puntos obtenidos.*/
float modoBmaquina(ifstream &file, int numCartas, float puntosHumano);


/* Recibe los puntos obtenidos por el jugador humano y por la máquina, y 
devuelve un valor que indica quién gana(1 = gana el humano, 2 = gana la máquina).*/
int determinaGanador(float puntosJugador, float puntosMaquina); 


/*En este modo C humano,el jugador no tiene limitacion en cuando a la hora
de robar cartas existentes del mazo.*/
float modoCmaquina(ifstream &file, tCartasPorAparecer cartas, float puntosHumano);

/* Permite realizar el turno del jugador máquina en el modo C. Recibe el archivo 
con el mazo, una variable cartas que indica cuántas cartas de cada tipo quedan y 
devuelve los puntos obtenidos y actualiza cartas de acuerdo con las cartas que 
haya robado la máquina. */
float modoCmaquina(ifstream &file, tCartasPorAparecer cartas, float puntosHumano);

/* Determina si la probabilidad que tiene la máquina de pasarse si robara una 
carta más es mayor que 0.5.Recibe la puntuación actual de la máquina y una variable
cartas que indica cuántas cartas de cada tipo quedan, y devuelve true si la
probabilidad de pasarse si roba una carta más supera 0.5 y false en caso contrario. */
bool esProbablePasarse(float puntosMaquina, const tCartasPorAparecer cartas);


/* Permite realizar el turno
del jugador humano en el modo D. Recibe el mazo y una variable
cartas que indica cuántas cartas de cada tipo quedan en el mazo; al
finalizar su ejecución deja cartas y mazo actualizados según las
cartas que haya robado el humano en su turno y devuelve los puntos
obtenidos por el humano así como las cartas que ha robado.*/
float modoDhumano(tConjuntoCartas &mazo, tCartasPorAparecer cartas, tConjuntoCartas &cartasHumano);

/*Permite realizar el turno del jugador máquina en el modo D. Recibe
el mazo, una variable cartas que indica cuántas cartas de cada tipo
quedan en el mazo y la puntuación obtenida por el jugador humano;
al finalizar su ejecución deja cartas y mazo actualizados según las
cartas que haya robado la máquina en su turno y devuelve los puntos
obtenidos por la máquina así como las cartas que ha robado.*/
float modoDmaquina(tConjuntoCartas &mazo, tCartasPorAparecer cartas, tConjuntoCartas &cartasMaquina, float puntosHumano);

/*--------------------------------------------------------------------------
						Subprogramas opcionales
--------------------------------------------------------------------------*/

/*Lleva la logica principal del juego para el modoA y modoB*/
bool juego(int opcion);

/*ejecuta el programa*/
void run(string yourname);

/* Muestra el menu del juego y pide al usuario una opcion  y lo devuelve*/
int menu(string nickname);

/* Cuenta el numero total de cartas y devuelve true si el numero es positivo */
bool quedanCartas(const tCartasPorAparecer cartas);

/*Elimina las cartas sacadas del array mazo*/
void eliminarCartasDelMazo(tCartasPorAparecer cartas, int cartaSacada);

// Inicializa mazo a la lista vacia.
void inicializa(tConjuntoCartas &mazo);


// Rellena mazo con 40 cartasdispuestas de forma aleatoria.
void crearMazo(tConjuntoCartas &mazo);

/*Elimina una carta de un extremo de la lista mazo y la devuelve en carta.*/
void sacarCarta(tConjuntoCartas &mazo, int &carta);

/*Añade la carta carta en un extremo de la lista mazo.*/
void annadirCarta(tConjuntoCartas &mazo, int carta);

/* Nueva función juego con las cartas en memoria en lugar de archivo */
void juegoModoD(int numPartida);

/*Determina el ganador del modo D*/
int determinaGanadorD(float puntosHumano, float puntosMaquina, int numCartasHumano, int numCartasMaquina);

/*Escribe el resultado en un fichero salida txt*/
void escribeArchivo(int numPartida, int gana, float puntosHumano, float puntosMaquina, tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina);

/*Imprime las cartas del mazo*/
void imprimeCartasArchivo(ofstream &outFile, tConjuntoCartas mazo);

//imprime por pantalla el contenido del fichero
void imprimePantalla(int numPartida);
/*--------------------------------------------------------------------------
						Funcion principal del programa
--------------------------------------------------------------------------*/
int main() {

	string yourname; //nombre de player

	cout << " ***************************************************** " << endl;
	cout << setw(50) << " Welcome to the <Las Siete y Medias> game. " << endl;
	cout << " ***************************************************** " << endl;
	cout << " Please enter your name and we can start the game : ";
	getline(cin,yourname); 

	//arrancamos el programa
	run(yourname);

	return 0;
}

/*--------------------------------------------------------------------------
					Implementacion		Subprogramas
--------------------------------------------------------------------------*/
void run(string yourname) {

	//Genera la semilla para posterior secuencia de nºaleatorios
	srand(time(NULL)); 

	short int	num_cards = 0,			//num de cartas aleatorias
				opt,				//variable para menu
				numPartida = 0;		//numero de partida inicial
	
	do {
		switch (opt = menu(yourname))
		{
			case 1:{
				system("cls");
				cout << "________You are playing modo A________" << endl;
				juego(opt);
				break; 
			}
			case 2: {
				system("cls");
				cout << "________You are playing modo B________" << endl;
				juego(opt);
				break;
			}
			case 3: {
				system("cls");
				cout << "________You are playing modo C________" << endl;
				juego(opt);
				break;
			}
			case 4: {
				system("cls");
				cout << "________You are playing modo D________" << endl;

				//incrementamos el numero de partida
				numPartida++;
				juegoModoD( numPartida);
				imprimePantalla(numPartida);
				break;
			}
			case 0: {
				system("cls");
				cout << "Gracias por jugar !!!" << endl;
				break;
			}
			default: {
				system("cls");
				cout << "****ERROR: Introduzca una option correcta: " << endl;
				cin.ignore();
				cin.get();
				break;
			}
		}
	} while (opt != 0);
	
}

int menu(string nickname) {

	short int option = 0;

	system("cls");
	cout << "Hello " << nickname << "! Lets play, choose one option!" << endl;

	cout << " *************************" << endl;
	cout <<setw(15)<< "1.Mode A." << endl;
	cout << setw(15) << "2.Mode B." << endl;
	cout << setw(15) << "3.Mode C." << endl;
	cout << setw(15) << "4.Mode D." << endl;
	cout << setw(13) << "0.Exit." << endl;
	cout << " *************************" << endl;
	cin.sync();
	cin >> option;

	return option;
}
		
float modoA(ifstream &file, int numCartas) {
	bool ok = true;			//condicion booleana para salir del bucle
	float	score = 0.0;	//puntuacion
	short int cards;	    //cartas

		int i = 1;
		cout << "------------------------------------" << endl;
		while (ok && !file.eof() && i <= numCartas ) {
			file >> cards;
			cout<< i << ".Card: " << cards << "  " ;
			if (cards > 7) {
				score += 0.5;
				cout << "SCORE: " << score << endl;
			}
			else {
				score += cards;
				cout << "SCORE: " << score << endl;
			}

			if (score > 7.5) {
				ok = false;
			}
			++i;
		}
			cout << "------------------------------------" << endl;
			
		return score;
	
}

int determinaGanador(float puntosJugador, float puntosMaquina) {
	//1 = gana el humano, 2 = gana la máquina
	short int winner;

	if (puntosJugador > 7.5) {
		winner = 2;
	}
	else if (puntosMaquina > 7.5) {
		winner = 1;
	}
	else {
		if (puntosJugador > puntosMaquina ) {	     //si gana humano
			winner = 1;
		}
		else if (puntosMaquina > puntosJugador) {	 //si gana maquina
			winner = 2;
		}
		else {										//otros casos se genera un nº aleatorio
			winner = 1 + rand() % (2 + 1 - 1);	    //que determina el ganador (1 o 2)
		}
	}
	return winner;
}

float modoBhumano(ifstream &file, int numCartas) {
	bool ok = true;			//para parar de robar cartas del mazo
	char answer = ' ';		//variable que guarda respuesta de plantarse
	float score = 0.0;	//puntuacion
	short int cards;	    //cartas del mazo

	int i = 1;
	cout << "------------------------------------" << endl;
	while (ok && !file.eof() && i <= numCartas) {
		file >> cards;
		cout << i << ".Card: " << cards << "  ";
		if (cards > 7) {
			score += 0.5;
			cout << "SCORE: " << score << endl;
		}
		else {
			score += cards;
			cout << "SCORE: " << score << endl;
		}

		if (score > 7.5) {
			ok = false;
		}
		else {
			if (i < numCartas) {
				//pregunta al jugador si desea plantarse
				cout << "Tu puntuacion es : " << score << ".Desea plantarse? (y/n): ";
				cin.ignore();
				cin >> answer;
				//si introduce y/Y dejamos de robar carta y salimos del bucle
				if (toupper(answer) == 'Y') {
					ok = false;
				}
			}
		}
		++i;
	}
	cout << "------------------------------------" << endl;

	return score;
}

float modoBmaquina(ifstream &file, int numCartas, float puntosHumano) {

	bool ok = true;			//para parar de robar cartas del mazo
	float	score = 0.0;	//puntuacion
	short int cards;	    //cartas del mazo

	int i = 1;
	cout << "------------------------------------" << endl;
	while (ok && !file.eof() && i <= numCartas) {
		file >> cards;
		cout << i << ".Card: " << cards << "  ";
		if (cards > 7) {
			score += 0.5;
			cout << "SCORE: " << score << endl;
		}
		else {
			score += cards;
			cout << "SCORE: " << score << endl;
		}

		if (score > 7.5) {
			ok = false;
		}
		else {
			//la maquina se plamta una vez que supere la puntuacion humana
			if (puntosHumano < score) {				
				cout << "La maquina ha plantado y su puntuacion es : " << score << " ." << endl;
				ok = false;
			}
		}
		++i;
	}
	cout << "------------------------------------" << endl;

	return score;
}

void eliminarCartasDelMazo(tCartasPorAparecer cartas, int cartaSacada) {

	switch (cartaSacada)
	{
	case 1: {
		cartas[0] -= 1;
		break;
	}
	case 2: {
		cartas[1] -= 1;
		break;
	}
	case 3: {
		cartas[2] -= 1;
		break;
	}
	case 4: {
		cartas[3] -= 1;
		break;
	}
	case 5: {
		cartas[4] -= 1;
		break;
	}
	case 6: {
		cartas[5] -= 1;
		break;
	}
	case 7: {
		cartas[6] -= 1;
		break;
	}
	case 10: {
		cartas[7] -= 1;
		break;
	}
	case 11: {
		cartas[8] -= 1;
		break;
	}
	case 12: {
		cartas[9] -= 1;
		break;
	}
	default:
		break;
	}
}

float modoChumano(ifstream &file, tCartasPorAparecer cartas) {
	bool ok = true;			//para parar de robar cartas del mazo
	char answer = ' ';		//variable que guarda respuesta de plantarse
	float	score = 0.0;	//puntuacion
	int cards;				//cartas del mazo

	int i = 1;
	cout << "------------------------------------" << endl;
	while (quedanCartas(cartas) && ok && !file.eof()) {
		file >> cards;
		cout << i << ".Card: " << cards << "  ";
		if (cards > 7) {
			score += 0.5;
			cout << "SCORE: " << score << endl;
			eliminarCartasDelMazo(cartas, cards);
			
			for (int i = 0; i < N; ++i) {
				if (i > 6) {
					cout << " | " << i + 3 << " | " << cartas[i] << endl;
				}
				else {
					cout << " | " << setw(2) << i + 1 << " | " << cartas[i] << endl;
				}
			}
		}
		else {
			//quitamos la carta correspondiente del array mazo
			eliminarCartasDelMazo(cartas, cards);
			score += cards;
			cout << "SCORE: " << score << endl;
			for (int i = 0; i < N; ++i) {
				if (i > 6) {
					cout << " | " << i + 3 << " | " << cartas[i] << endl;
				}
				else {
					cout << " | " << setw(2) << i + 1 << " | " << cartas[i] << endl;
				}
			}
		}

		if (score > 7.5) {
			ok = false;
		}
		else {
			//pregunta al jugador si desea plantarse
			cout << "Tu puntuacion es : " << score << ".Desea plantarse? (y/n): ";
			cin.ignore();
			cin >> answer;
			if (toupper(answer) == 'Y') {
				ok = false;
			}

		}
		++i;
	}
	cout << "------------------------------------" << endl;

	return score;
}


bool juego(int opcion) {
	bool ok = true;	   //si se ha abierto correctamente el input file
	string file_name;  //nombre del fichero
	ifstream file;	   //input file

	cout << "Enter input file name : ";
	cin.sync();
	cin >> file_name;

	//preparando para abrir
	file.open(file_name + ".txt");

	//si no se abre correctamente
	if (file.fail()) {			   
		cerr << "*** ERROR: Cannot open " << file_name + ".txt" << " for input." << endl;
		ok = false;
	}
	//si el archivo se ha abierto correctamente
	else {						  
		//modoA
		if (opcion == 1) {
			//numero aleatorio
			short int numCartas = 3 + rand() % (5 + 1 - 3); 
			cout << "For this game you will get : " << numCartas << " cards !" << endl;

			cout << "------------------------------------" << endl << setw(20) << "Player turn" << endl;
			float puntuacionHumano = modoA(file, numCartas);

			if (puntuacionHumano > 7.5) {
				cout << "******* Machine wins! *******" << endl;
			}
			else {
				cout << setw(20) <<  "Machine turn" << endl;
				float puntuacionMaquina = modoA(file, numCartas);

				if (puntuacionMaquina > 7.5) {
					cout << "******* Player wins! *******" << endl;
				}
				else {
					//determina el ganador
					int ganador = determinaGanador(puntuacionHumano, puntuacionMaquina);	
					if (ganador == 1) {
						cout << "******* Player wins! *******" << endl;
					}
					else {
						cout << "******* Machine wins! *******" << endl;
					}
				}
			}
		}
		//modoB
		else if (opcion == 2) {		
			//numero aleatorio
			short int numCartas = 3 + rand() % (5 + 1 - 3); 
			cout << "For this game you will get : " << numCartas << " cards !" << endl;

			cout << "------------------------------------" << endl << setw(20) << "Player turn" << endl;
			float puntuacionHumano = modoBhumano(file, numCartas);
			//comprueba si el player ha superado las 7.5
			if (puntuacionHumano > 7.5) {		
				cout << "******* Machine wins! ********" << endl;
			}
			//si no supera,turno de la maquina
			else {												
				cout << setw(20) << "Machine turn" << endl;
				float puntuacionMaquina = modoBmaquina(file, numCartas, puntuacionHumano);
				//determina quien ha ganado
				int ganador = determinaGanador(puntuacionHumano, puntuacionMaquina);	

				if (ganador == 1) {
					cout << "******* Player wins! *******" << endl;
				}
				else {
					cout << "******* Machine wins! ********" << endl;
				}
			}
		}
		//version 2 modo C
		else if (opcion == 3) { 
			system("cls");
			//iniciamos el array con 4 cartas en cada posicion
			tCartasPorAparecer cartas;
			cout << "------------------------------------" << endl << setw(20) << "Player turn" << endl;
			for (int i = 0; i < N; ++i) {
				cartas[i] = 4;
			}
		
			float puntuacionHumano = modoChumano(file, cartas);
			//comprueba si el player ha superado las 7.5
			if (puntuacionHumano > 7.5) {		
				cout << "******* Machine wins! ********" << endl;
			}
			//si no supera,turno de la maquina	
			else {										
				cout << setw(20) << "Machine turn" << endl;
				float puntuacionMaquina = modoCmaquina(file, cartas, puntuacionHumano);
				//determina quien ha ganado
				int ganador = determinaGanador(puntuacionHumano, puntuacionMaquina);

				if (ganador == 1) {
					cout << "******* Player wins! *******" << endl;
				}
				else {
					cout << "******* Machine wins! ********" << endl;
				}
			}

		}
		else {
			cout << "***ERROR" << endl;
			ok = false;
		}
	}
	
	//cierre del archivo
	file.close();	
	//para ver el resultado tras ejecutar
	cin.ignore();	
	cin.get();

	return ok;
}


bool quedanCartas(const tCartasPorAparecer cartas) {
	int total = 0; 
	//recorremos el array
	for (int i = 0; i < N; ++i) {
	//sumamos las cartas que hay
		total += cartas[i];
	}
	return (total > 0);
}

bool esProbablePasarse(float puntosMaquina, const tCartasPorAparecer cartas) {
	int cartasMalas = 0, total = 0;
	double diferencia = 7.5 - puntosMaquina;
	bool ok = false;

	//calculamos las cartas malas que hay en el mazo
	for (int i = 0; i < N; ++i) {
		total += cartas[i];
		if (i < 7 && diferencia < i + 1) {
			cartasMalas += cartas[i];
		}
		else if (i >= 7 && diferencia < 0.5) {
			cartasMalas += cartas[i];
		}
	}
	double estimacion = (double)cartasMalas / total;
	cout << "Total cartas restantes : " << total << endl <<
		"Total cartas malas: " << cartasMalas << endl;

	cout << "Probabilidad de pasarse:" << estimacion <<  endl;

	//si es mayor que 50% 
	if (estimacion > 0.5) {
		ok = true;
	}
	return ok;
}

float modoCmaquina(ifstream &file, tCartasPorAparecer cartas, float puntosHumano) {
	bool ok = true;			//para parar de robar cartas del mazo
	float	score = 0.0;	//puntuacion
	short int cards;		//cartas del mazo

	int i = 1;
	cout << "------------------------------------" << endl;
	while (quedanCartas(cartas) && ok && !file.eof()) {
		file >> cards;
		cout << i << ".Card: " << cards << "  ";
		if (cards > 7) {
			score += 0.5;
			cout << "SCORE: " << score << endl;
			eliminarCartasDelMazo(cartas, cards);
			for (int i = 0; i < N; ++i) {
				if (i > 6) {
					cout  << " | " << i + 3 << " | " << cartas[i] << endl;
				}
				else {
					cout  << " | " << setw(2) << i + 1 << " | " << cartas[i] << endl;
				}
			}
		}
		else {
			//quitamos la carta correspondiente del array
			eliminarCartasDelMazo(cartas, cards); 
			score += cards;
			cout << "SCORE: " << score << endl;
			for (int i = 0; i < N; ++i) {
				if (i > 6) {
					cout <<  " | " << i + 3 << " | " << cartas[i] << endl;
				}
				else {
					cout  << " | " << setw(2) << i + 1 << " | " << cartas[i] << endl;
				}
			}
		}

		if (score > 7.5) {
			ok = false;
			cout << "La maquina se ha pasado !" << endl;
		}
		else {
			if (quedanCartas(cartas)) {
				if (score == 7.5 || score > puntosHumano || (score == puntosHumano && esProbablePasarse(score, cartas))) {
					ok = false;
					cout << "La maquina ha plantado y su puntuacion es : " << score << " ." << endl;
				}
			}
		
		}
		++i;
	}
	cout << "------------------------------------" << endl;

	return score;
}


void inicializa(tConjuntoCartas &mazo) {
	//inicializamos el mazo a 0 y el contador a 0
	for (int i = 0; i < M; ++i) {
		mazo.lista[i] = 0;
	}
	mazo.contador = 0;
}

void crearMazo(tConjuntoCartas &mazo) {
	
	//Rellenar el mazo con 40 cartas (pueden estar ordenadas) y lo visualiza sin barajar
	for (int i = 0; i <4; ++i) {
		for (int j = 1; j <= 7; ++j) {
			mazo.lista[mazo.contador] = j;
			mazo.contador++;
		}
		for (int z = 10; z <= 12; ++z) {
			mazo.lista[mazo.contador] = z;
			mazo.contador++;
		}
	}
	cout << endl << "--------------------------------------------" << endl;
	cout << "Antes de ordenar la baraja hay: " << mazo.contador << " cartas." << endl;
	cout << "--------------------------------------------" << endl;

	for (int i = 0; i < M; ++i) {
		cout << setw(2) << i + 1 << " - Carta: " << setw(2) << mazo.lista[i] << endl;
	}
	
	//procedemos a barajar la baraja utilizando la libreria  <algorithm> 
	random_shuffle(&(mazo.lista[0]), &(mazo.lista[M-1]));

	cout << endl << "--------------------------------------------" << endl;
	cout << "Despues de ordenar la baraja hay: " << mazo.contador << " cartas." << endl;
	cout << "--------------------------------------------" << endl;
	for (int i = 0; i < M; ++i) {
		cout << setw(2) << i + 1 << " - Carta: " << setw(2) << mazo.lista[i] << endl;
	}
	
}

/*Elimina una carta de un extremo de la lista mazo y la devuelve en carta.*/
void sacarCarta(tConjuntoCartas &mazo, int &carta) {
	bool ok = true;

	if (ok && mazo.contador != 0) {
		//quitamos la carta ultima del mazo
		carta = mazo.lista[mazo.contador - 1];
		//disminuimos el contador de cartas
		mazo.contador--;
		
		/*for (int i = 1; i < mazo.contador; ++i) {
			mazo.lista[i - 1] = mazo.lista[i]; //movemos las cartas a la izquierda					
		}*/
		
		//asignamos a la ultima posicion del array un 0 ,
		mazo.lista[mazo.contador] = 0;
	}	
	else {
		ok = false;
	}
}

/*Añade la carta carta en un extremo de la lista mazo.*/
void annadirCarta(tConjuntoCartas &mazo, int carta) {
	bool ok = true;
	if (ok && mazo.contador != M) {
		mazo.lista[mazo.contador] = carta;
		mazo.contador++;
	}
	else {
		ok = false;
	}
}

void juegoModoD(int numPartida) {
	float playerScore = 0.0, machineScore = 0.0;
	 
	tConjuntoCartas mazo, cartasHumano, cartasMaquina;
	inicializa(mazo); 
	inicializa(cartasHumano);
	inicializa(cartasMaquina);
	crearMazo(mazo);
	
	int ganador = 0, manoHumano = 0, manoMaquina = 0; // ganador de la partida
	
	//iniciamos el array con 4 cartas en cada posicion
	tCartasPorAparecer cartas;
	cout << "------------------------------------" << endl << setw(20) << "Player turn" << endl;
	for (int i = 0; i < N; ++i) {
		cartas[i] = 4;
	}
	cout << "------------------------------------" << endl;
	playerScore = modoDhumano(mazo,cartas,cartasHumano);
	cout << "PLayer score:" << playerScore << " ..." << endl;
	cout << "------------------------------------" << endl;
	//comprueba si el player ha superado las 7.5
	if (playerScore > 7.5) {		
		cout << "******* Machine wins! ********" << endl;
		ganador = 2;
		manoHumano = cartasHumano.contador;

	}
	//si no supera,turno de la maquina	
	else {										
		cout << "------------------------------------" << endl;
		cout << setw(20) << "Machine turn" << endl;
		machineScore = modoDmaquina(mazo, cartas, cartasMaquina, playerScore);
		manoMaquina = cartasMaquina.contador;
		if (machineScore > 7.5) {
			cout << "******* Player wins! *******" << endl;
			//gana  el jugador humano
			ganador = 1;
		}
		else {
			ganador =  determinaGanadorD(playerScore, machineScore, manoHumano, manoMaquina);
			if (ganador == 1) {
				cout << "******* Player wins! *******" << endl;
			}
			else {
				cout << "******* Machine wins! ********" << endl;
			}
		}
	}
	cout << "------------------------------------" << endl;

	escribeArchivo(numPartida, ganador, playerScore,machineScore, cartasHumano, cartasMaquina);
}	

float modoDhumano(tConjuntoCartas &mazo, tCartasPorAparecer cartas, tConjuntoCartas &cartasHumano) {
	bool ok = true;			//para parar de robar cartas del mazo
	char answer = ' ';		//variable que guarda respuesta de plantarse
	float	score = 0.0;	//puntuacion
	int carta;				//cartas del mazo

	int i = 1;
	while (ok && mazo.contador != 0 && cartasHumano.contador < M) {
		sacarCarta(mazo,carta);
		annadirCarta(cartasHumano, carta);
		cout << "------------------------------------" << endl;
		cout << i << ".Card: " << carta << "  ";
		if (carta > 7) {
			score += 0.5;
			cout << "SCORE: " << score << endl << "Despues de eliminar la carta del mazo quedan :" << endl;
			eliminarCartasDelMazo(cartas, carta);
			for (int i = 0; i < N; ++i) {
				if (i > 6) {
					cout << " | " << i + 3 << " | " << cartas[i] << endl;
				}
				else {
					cout << " | " << setw(2) << i + 1 << " | " << cartas[i] << endl;
				}
			}
		}
		else {
			//quitamos la carta correspondiente del array
			score += carta;
			eliminarCartasDelMazo(cartas, carta); 
			cout << "SCORE: " << score << endl << "Despues de eliminar la carta del mazo quedan :" << endl;
			for (int i = 0; i < N; ++i) {
				if (i > 6) {
					cout << " | " << i + 3 << " | " << cartas[i] << endl;
				}
				else {
					cout << " | " << setw(2) << i + 1 << " | " << cartas[i] << endl;
				}
			}
			cout << "------------------------------------" << endl;
		}
		if (score > 7.5) {
			ok = false;
		}
		else {
			//pregunta al jugador si desea plantarse
			cout << "Tu puntuacion es : " << score << ".Desea plantarse? (y/n): ";
			cin.ignore();
			cin >> answer;
			if (toupper(answer) == 'Y') {
				ok = false;
			}

		}
		++i;
	} 
	cout << "------------------------------------" << endl;
	cout << "Las cartas que tienes en la mano son :" << endl << " | ";
	for (int i = 0; i < cartasHumano.contador; ++i) {
		cout << cartasHumano.lista[i] << " | ";
	}
	cout << endl <<  "------------------------------------" << endl;
	return score;
}


float modoDmaquina(tConjuntoCartas &mazo, tCartasPorAparecer cartas, tConjuntoCartas &cartasMaquina, float puntosHumano) {
	bool ok = true;			//para parar de robar cartas del mazo
	float	score = 0.0;	//puntuacion
	int carta = 0;			//cartas del mazo

	int i = 1;
	cout << "------------------------------------" << endl;
	while (ok && mazo.contador != 0 && cartasMaquina.contador < M) {
		sacarCarta(mazo, carta);
		annadirCarta(cartasMaquina, carta);
		
		cout << i << ".Card: " << carta << "  ";
		if (carta > 7) {
			score += 0.5;
			eliminarCartasDelMazo(cartas, carta);
			cout << "SCORE: " << score << endl << "Despues de eliminar la carta del mazo quedan :" << endl;
			for (int i = 0; i < N; ++i) {
				if (i > 6) {
					cout << " | " << i + 3 << " | " << cartas[i] << endl;
				}
				else {
					cout << " | " << setw(2) << i + 1 << " | " << cartas[i] << endl;
				}
			}
		}
		else {
			//quitamos la carta correspondiente del array
			eliminarCartasDelMazo(cartas, carta); 
			score += carta;
			cout << "SCORE: " << score << endl << "Despues de eliminar la carta del mazo quedan :" << endl;
			for (int i = 0; i < N; ++i) {
				if (i > 6) {
					cout << " | " << i + 3 << " | " << cartas[i] << endl;
				}
				else {
					cout << " | " << setw(2) << i + 1 << " | " << cartas[i] << endl;
				}
			}
		}
		cout << "------------------------------------" << endl;
		if (score > 7.5) {
			ok = false;
			cout << "La maquina se ha pasado !" << endl;
		}
		else {
			if (mazo.contador != 0) {
				if (score == 7.5 || score > puntosHumano || (score == puntosHumano && esProbablePasarse(score, cartas))) {
					ok = false;
					cout << "La maquina ha plantado y su puntuacion es : " << score << " ." << endl;
				}
			}

		}
		++i;
	}
	cout << "------------------------------------" << endl;
	cout << "Las cartas que tienes en la mano son :" << endl << " | ";
	for (int i = 0; i < cartasMaquina.contador; ++i) {
		cout << cartasMaquina.lista[i] << " | ";
	}
	cout << endl <<  "------------------------------------" << endl;

	return score;
}

int determinaGanadorD(float puntosHumano, float puntosMaquina, int numCartasHumano, int numCartasMaquina) {
	//1 = gana el humano, 2 = gana la máquina
	short int winner;

	if (puntosHumano > puntosMaquina) {
		winner = 1;
	}
	else if (puntosMaquina > puntosHumano) {
		winner = 2;
	}
	else {
		if (numCartasHumano ==  numCartasMaquina) {	    
			winner = 1 + rand() % (2 + 1 - 1);
		}
		else {
			if (numCartasHumano < numCartasMaquina) {
				winner = 1;
			}
			else {
				winner = 2;
			}
		}
	}
	return winner;
}

void escribeArchivo(int numPartida, int gana, float puntosHumano, float puntosMaquina, tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina) {
	ofstream outFile;

	outFile.open(to_string(numPartida) + ".txt");
	if (outFile.is_open()) {
		outFile << "*****************************************"
			<< endl <<setw(30)<< "Numero de Partida: " << numPartida << endl <<
			"*****************************************" << endl;
		if (gana == 1) {
			outFile << "----------------------------------------" << endl << setw(28)<< "Ganador: HUMANO " << endl << "----------------------------------------" << endl;
		}
		else {
			outFile << "----------------------------------------" << endl << setw (28)<<"Ganador: MAQUINA." << endl << "----------------------------------------" << endl;
		}

		outFile << "Resultado HUMANO" << endl << "***Puntuacion HUMANO: " << puntosHumano << endl
			<< "Las cartas que ha sacado la maquina son:" << endl;
		imprimeCartasArchivo(outFile, cartasHumano);
		outFile << endl << "----------------------------------------" << endl;
		outFile << "Resultado MAQUINA" << endl << "***Puntuacion MAQUINA: " << puntosMaquina << endl
			<< "Las cartas que ha sacado la maquina son:" << endl;
		imprimeCartasArchivo(outFile, cartasMaquina);
		outFile << endl;

		outFile.close();
	}
	else {
		cerr << "***ERROR: cant find the file." << endl;
	}
}


void imprimeCartasArchivo(ofstream &outFile, tConjuntoCartas mazo) {
	
	if(mazo.contador!=0){
		outFile << " | ";
	}
	else {
		outFile << "No ha necesitado robar cartas." << endl;
	}
	
	if (outFile.is_open()) {
		for (int i = 0; i < M; ++i) {
			if (mazo.lista[i] != 0) {
				outFile << mazo.lista[i] << " | ";
			}
		}
	}
	else {
		cerr << "***ERROR: cant find the file." << endl;
	}
}


void imprimePantalla( int numPartida) {
	ifstream inputFile;
	bool ok = true;
	string contenido = " ";
	cout << "=============================================================" << endl;
	cout << "A continuacion vamos a proceder a guardar los datos " << endl
		<< "de la partida en un finchero numPartida + .txt ." << endl
		<< 	"Se ha guardado los siguientes datos: " << endl;
	cout << "=============================================================" << endl;

	inputFile.open(to_string(numPartida) + ".txt");
	if (ok && inputFile.is_open()) {
		do {
			getline(inputFile, contenido);
			cout << contenido <<  endl;
		} while (!inputFile.eof());

		inputFile.close();
	}
	else {
		cerr << "***ERROR; cannot open the input file." << endl;
		ok = false;
	}

	cin.ignore();
	cin.get();
}