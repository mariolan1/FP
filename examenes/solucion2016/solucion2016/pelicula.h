#ifndef pelicula_h
#define pelicula_h
#include <fstream>
#include "reparto.h"

// Estructura de una pelicula
typedef struct {
    string titulo;
    string director;
    string genero;
    double valoracion;
    tReparto reparto;
} tPelicula;


// Carga la información de una pelicula
void cargar(tPelicula &pelicula, ifstream &archivo);

// Comprueba si un actor interviene en una pelicula
bool interviene(const tPelicula &pelicula, tActor actor);

// Muestra la información de una película
void mostrar(const tPelicula &pelicula);

#endif
