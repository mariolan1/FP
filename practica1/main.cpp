
/*
	*Practica 1 FP Version 1.
	*Nombre y apellido : Wenhui Lin   
	*Nombre y apellido : Wenbo Sun
*/



/*--------------------------------------------------------------------------
								Librearias
--------------------------------------------------------------------------*/
#include <iostream> //console input and output
#include <iomanip>	//manipular espacios
#include <cstdlib>  //random
#include <string>	//for string variables
#include <fstream>	// for in/out put files

using namespace std;


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


/*--------------------------------------------------------------------------
						Subprogramas opcionales
--------------------------------------------------------------------------*/

/*Lleva la logica principal del juego para el modoA y modoB*/
bool juego(int opcion);

/*ejecuta el programa*/
void run(string yourname);

/* Muestra el menu del juego y pide al usuario una opcion  y lo devuelve*/
int menu(string nickname);



/*--------------------------------------------------------------------------
						Funcion principal del programa
--------------------------------------------------------------------------*/
int main() {

	string yourname; //nombre de player

	cout << " ***************************************************** " << endl;
	cout << setw(50) << " Welcome to the <Las Siete y Medias> game. " << endl;
	cout << " ***************************************************** " << endl;
	cout << " Please enter your name and we can start the game : ";
	cin >> yourname; 

	run(yourname);

	return 0;
}

/*--------------------------------------------------------------------------
					Implementacion		Subprogramas
--------------------------------------------------------------------------*/
void run(string yourname) {

	srand(time(NULL)); //Genera la semilla para posterior secuencia de nºaleatorios

	short int	num_cards, // num de cartas aleatorias
				opt;  //menu
	
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

	short int option = NULL; //local variable

	
	system("cls");
	cout << "Hello " << nickname << "! Lets play, choose one option!" << endl;

	cout << " *************************" << endl;
	cout <<setw(15)<< "1.Mode A." << endl;
	cout << setw(15) << "2.Mode B." << endl;
	cout << setw(13) << "0.Exit." << endl;
	cout << " *************************" << endl;
	cin.sync();
	cin >> option;

	return option;
}
		
float modoA(ifstream &file, int numCartas) {
	bool ok = true;
	float	score = 0.0;	//puntuacion
	short int cards;	    //cartas del mazo

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
			winner = 1 + rand() % (2 + 1 - 1);	    //que determina el ganador 
		}
	}
	return winner;
}

float modoBhumano(ifstream &file, int numCartas) {
	bool ok = true;			//para parar de robar cartas del mazo
	char answer = ' ';		//variable que guarda respuesta de plantarse
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
			if (i < numCartas) {		//pregunta al jugador si desea plantarse
				cout << "Tu puntuacion es : " << score << ".Desea plantarse? (y/n): ";
				cin.ignore();
				cin >> answer;
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
			if (puntosHumano < score) {				//la maquina se plamta una vez que supere la puntuacion humana
				cout << "La maquina ha plantado y su puntuacion es : " << score << " ." << endl;
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

	short int numCartas = 3 + rand() % (5 + 1 - 3);  //numero aleatorio

	cout << "For this game you will get : " << numCartas << " cards !" << endl << "Enter input file name : ";
	cin.sync();
	cin >> file_name;

	file.open(file_name + ".txt"); //preparando para abrir
	if (file.fail()) {			   //si no se abre correctamente
		cerr << "*** ERROR: Cannot open " << file_name + ".txt" << " for input." << endl;
		ok = false;
	}
	else {						  //si el archivo se ha abierto correctamente
		cout << "------------------------------------" << endl << setw(20) << "Player turn" << endl;
		if (opcion == 1) {		  //modoA
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
					int ganador = determinaGanador(puntuacionHumano, puntuacionMaquina);	//determina el ganador
					if (ganador == 1) {
						cout << "******* Player wins! *******" << endl;
					}
					else {
						cout << "******* Machine wins! *******" << endl;
					}
				}
			}
		}
		else {					 //modoB
			float puntuacionHumano = modoBhumano(file, numCartas);

			if (puntuacionHumano > 7.5) {		//comprueba si el player ha superado las 7.5
				cout << "******* Machine wins! ********" << endl;
			}
			else {								//si no supera,turno de la maquina				
				cout << setw(20) << "Machine turn" << endl;
				float puntuacionMaquina = modoBmaquina(file, numCartas, puntuacionHumano);
				int ganador = determinaGanador(puntuacionHumano, puntuacionMaquina);	//determina quien ha ganado

				if (ganador == 1) {
					cout << "******* Player wins! *******" << endl;
				}
				else {
					cout << "******* Machine wins! ********" << endl;
				}
			}
		}
	}
	

	file.close();	//cierre del archivo
	
	cin.ignore();	//para ver el resultado tras ejecutar
	cin.get();

	return ok;
}