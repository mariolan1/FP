#include <iostream>
#include <iomanip>
#include "pelicula.h"
#include "checkML.h"
using namespace std;


void cargar(tPelicula &pelicula, ifstream &archivo) {
    getline(archivo, pelicula.titulo);
    getline(archivo, pelicula.director);
    getline(archivo, pelicula.genero);
    archivo >> pelicula.valoracion;
    cargar(pelicula.reparto, archivo);
} // cargar


bool interviene(const tPelicula &pelicula, tActor actor) {
    bool interviene = false;
    aparece(pelicula.reparto, interviene, actor, 0);
    return interviene;
} // interviene


void mostrar(const tPelicula &pelicula) {
    cout << fixed << left << setw(12) << "Titulo:" << pelicula.titulo << endl;
    cout << fixed << left << setw(12) << "Director:" << pelicula.director << endl;
    cout << fixed << left << setw(12) << "Genero:" << pelicula.genero << endl;
    cout << fixed << left << setw(12) << "Valoracion:" << setprecision(1) << pelicula.valoracion << endl;
} // mostrar
