#include <fstream>
#include <string>
#include <iostream>
#include "reparto.h"
#include "checkML.h"
using namespace std;


void cargar(tReparto &reparto, ifstream &archivo) {
    int num, i = 0;
    tActor actor;
    reparto.contador = 0;
    archivo >> num;
    while (i <= num) {
        getline(archivo, actor.nombre);
        reparto.actores[i] = actor;
        reparto.contador++;
        i++;
    }
} // cargar


void aparece(const tReparto &reparto, bool &existe, tActor actor, int pos) {
    if (pos < reparto.contador)	{
        if (reparto.actores[pos].nombre == actor.nombre) {
            existe = true;	
        }
        aparece(reparto, existe, actor, pos + 1);
    }
} // aparece
