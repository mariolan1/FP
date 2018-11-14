
/*
	*Practica 1 FP Version 2.
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
						Tipos definidos
--------------------------------------------------------------------------*/

const int N = 10; // constante del array
typedef int tCartasPorAparecer[N]; //array

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
			case 3: {
				system("cls");
				cout << "________You are playing modo C________" << endl;
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
	cout << setw(15) << "3.Mode C." << endl;
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
	int cards;	    //cartas del mazo

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
			eliminarCartasDelMazo(cartas, cards); //quitamos la carta correspondiente del array
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

	file.open(file_name + ".txt"); //preparando para abrir
	if (file.fail()) {			   //si no se abre correctamente
		cerr << "*** ERROR: Cannot open " << file_name + ".txt" << " for input." << endl;
		ok = false;
	}
	else {						  //si el archivo se ha abierto correctamente
		
		if (opcion == 1) {		  //modoA
			short int numCartas = 3 + rand() % (5 + 1 - 3);  //numero aleatorio
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
		else if (opcion == 2) {					 //modoB
			short int numCartas = 3 + rand() % (5 + 1 - 3);  //numero aleatorio
			cout << "For this game you will get : " << numCartas << " cards !" << endl;

			cout << "------------------------------------" << endl << setw(20) << "Player turn" << endl;
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
		else if (opcion == 3) { //version 2

			system("cls");
			//iniciamos el array con 4 cartas en cada posicion
			tCartasPorAparecer cartas;
			cout << "------------------------------------" << endl << setw(20) << "Player turn" << endl;
			for (int i = 0; i < N; ++i) {
				cartas[i] = 4;
			}
		
			float puntuacionHumano = modoChumano(file, cartas);

			if (puntuacionHumano > 7.5) {		//comprueba si el player ha superado las 7.5
				cout << "******* Machine wins! ********" << endl;
			}
			else {								//si no supera,turno de la maquina				
				cout << setw(20) << "Machine turn" << endl;
				float puntuacionMaquina = modoCmaquina(file, cartas, puntuacionHumano);
				int ganador = determinaGanador(puntuacionHumano, puntuacionMaquina);	//determina quien ha ganado

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
	

	file.close();	//cierre del archivo
	
	cin.ignore();	//para ver el resultado tras ejecutar
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
	float diferencia = 7.5 - puntosMaquina;
	bool ok = false;

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

	if (estimacion > 0.5) {
		ok = true;
	}
	return ok;
}

float modoCmaquina(ifstream &file, tCartasPorAparecer cartas, float puntosHumano) {
	bool ok = true;	//para parar de robar cartas del mazo
	float	score = 0.0;	//puntuacion
	short int cards;	//cartas del mazo

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
			eliminarCartasDelMazo(cartas, cards); //quitamos la carta correspondiente del array
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
